from __future__ import print_function, division, absolute_import

import sys
import os
import shlex
from subprocess import Popen, PIPE, STDOUT
from collections import defaultdict, namedtuple

from docutils import nodes
from docutils.parsers import rst
from docutils.parsers.rst.directives import flag, unchanged, nonnegative_int


class program_output_node(nodes.Element):
    pass


def _slice(value):
    parts = [int(v.strip()) for v in value.split(',')]
    if len(parts) > 2:
        raise ValueError('too many slice parts')
    return tuple((parts + [None] * 2)[:2])


class ProgramOutputDirective(rst.Directive):
    has_content = False
    final_argument_whitespace = True
    required_arguments = 1

    option_spec = dict(shell=flag, prompt=flag, nostderr=flag,
                       ellipsis=_slice, extraargs=unchanged,
                       returncode=nonnegative_int, cwd=unchanged)

    def run(self):
        env = self.state.document.settings.env

        node = program_output_node()
        node.line = self.lineno
        node['command'] = self.arguments[0]

        if self.name == 'command-output':
            node['show_prompt'] = True
        else:
            node['show_prompt'] = 'prompt' in self.options

        node['hide_standard_error'] = 'nostderr' in self.options
        node['extraargs'] = self.options.get('extraargs', '')
        _, cwd = env.relfn2path(self.options.get('cwd', '/'))
        node['working_directory'] = cwd
        node['use_shell'] = 'shell' in self.options
        node['returncode'] = self.options.get('returncode', 0)
        if 'ellipsis' in self.options:
            node['strip_lines'] = self.options['ellipsis']
        return [node]


_Command = namedtuple(
    'Command', 'command shell hide_standard_error working_directory')


class Command(_Command):
    """
    A command to be executed.
    """

    def __new__(cls, command, shell=False, hide_standard_error=False,
                working_directory='/'):
        if isinstance(command, list):
            command = tuple(command)
        # `chdir()` resolves symlinks, so we need to resolve them too for
        # caching to make sure that different symlinks to the same directory
        # don't result in different cache keys.  Also normalize paths to make
        # sure that identical paths are also equal as strings.
        working_directory = os.path.normpath(os.path.realpath(
            working_directory))
        return _Command.__new__(cls, command, shell, hide_standard_error,
                                working_directory)

    @classmethod
    def from_program_output_node(cls, node):
        """
        Create a command from a :class:`program_output_node`.
        """
        extraargs = node.get('extraargs', '')
        command = (node['command'] + ' ' + extraargs).strip()
        return cls(command, node['use_shell'],
                   node['hide_standard_error'], node['working_directory'])

    def execute(self):
        """
        Execute this command.

        Return the :class:`~subprocess.Popen` object representing the running
        command.
        """
        command = self.command
        if (bytes is str
                and not isinstance(command, str)
                and hasattr(command, 'encode')):
            # Python 2, given a unicode string
            command = command.encode(sys.getfilesystemencoding())
            assert isinstance(command, str)

        if not self.shell:
            if isinstance(command, str):
                command = shlex.split(command)
            else:
                command = self.command

        return Popen(command, shell=self.shell, stdout=PIPE,
                     stderr=PIPE if self.hide_standard_error else STDOUT,
                     cwd=self.working_directory)

    def get_output(self):
        """
        Get the output of this command.

        Return a tuple ``(returncode, output)``.  ``returncode`` is the
        integral return code of the process, ``output`` is the output as
        unicode string, with final trailing spaces and new lines stripped.
        """
        process = self.execute()
        output = process.communicate()[0].decode(
            sys.getfilesystemencoding(), 'replace').rstrip()
        return process.returncode, output

    def __str__(self):
        command = self.command
        command = list(command) if isinstance(command, tuple) else command
        return repr(command)

        return_code, result = command.get_output()
        self[command] = result
        return result


def run_programs(app, doctree):
    """
    Execute all programs represented by ``program_output_node`` nodes in
    ``doctree``.  Each ``program_output`` node in ``doctree`` is then
    replaced with a node, that represents the output of this program.

    The program output is retrieved from the cache in
    ``app.env.programoutput_cache``.
    """
    # The node_class used to be switchable to `sphinxcontrib.ansi.ansi_literal_block`
    # if `app.config.programoutput_use_ansi` was set. But sphinxcontrib.ansi
    # is no longer available on PyPI, so we can't test that. And if we can't test it,
    # we can't support it.
    node_class = nodes.literal_block


    for node in doctree.traverse(program_output_node):
        command = Command.from_program_output_node(node)
        try:
            returncode, output = command.get_output()
        except EnvironmentError as error:
            error_message = 'Command {0} failed: {1}'.format(command, error)
            error_node = doctree.reporter.error(error_message, base_node=node)
            node.replace_self(error_node)
        else:
            if returncode != node['returncode']:
                app.warn('Unexpected return code {0} from command {1}'.format(
                    returncode, command))

            # replace lines with ..., if ellipsis is specified
            if 'strip_lines' in node:
                lines = output.splitlines()
                start, stop = node['strip_lines']
                lines[start:stop] = ['...']
                output = '\n'.join(lines)

            if node['show_prompt']:
                tmpl = app.config.programoutput_prompt_template
                output = tmpl.format(command=node['command'], output=output,
                                     returncode=returncode)

            new_node = node_class(output, output)
            new_node['language'] = 'text'
            node.replace_self(new_node)


def setup(app):
    app.add_config_value('programoutput_prompt_template',
                         '$ {command}\n{output}', 'env')
    app.add_directive('program-output', ProgramOutputDirective)
    app.add_directive('command-output', ProgramOutputDirective)
    app.connect('doctree-read', run_programs)
    metadata = {
        'parallel_read_safe': True
    }
    return metadata
