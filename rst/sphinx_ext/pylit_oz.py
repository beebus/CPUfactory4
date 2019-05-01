# -*- coding: utf-8 -*-
"""
    sphinx.ext.pylit_oz
    ~~~~~~~~~~~~~~~~~~~

    Allow zed/oz specification blocks to be included in Sphinx-generated
    documents inline.

    :copyright: Copyright 2012 by the Roie Black
    :license: BSD, see LICENSE for details.
"""
from sphinx.errors import SphinxError
from sphinx.util.nodes import set_source_info
from docutils.parsers.rst  import Directive
from docutils import nodes, utils
from docutils.parsers.rst import directives

import os
import shutil
import hashlib
import posixpath

BUILD_TMPDIR = os.path.join(os.getcwd(),'latex','images')

class OzExtError(SphinxError):
    category = 'Oz Extension Error'

class RenderOzImage(object):

    def __init__(self, text, builder, font_size=11 ):
        #print("Rendering",text, os.getcwd())
        self.text = text
        self.builder = builder
        self.font_size = font_size
        self.imagedir = os.path.join(os.getcwd(),
                'latex','images')

    def render(self):
        '''return name of final image file'''
        # generate a unique name for the image
        shasum = "%s.png" % hashlib.md5(self.text.encode('utf-8')).hexdigest()
        relfn = posixpath.join(self.builder.imgpath, 'circuits',shasum)
        outfn = os.path.join(self.builder.outdir, 
                self.builder.imagedir, 'circuits', shasum)
        print("outfn:",outfn)
        print("relfn:",relfn)

        # see if we already have generated this image
        if os.path.exists(outfn):
            return relfn, outfn

        # create temp file for running latex
        print("Rendering latex image", shasum + '.png')
        tempdir = BUILD_TMPDIR
        curpath = os.getcwd()
        os.chdir(tempdir)

        # create the latex file to process
        self.wrap_text()

        # run pdflatex to build the dvi file
        status = os.system("pdflatex --interaction=nonstopmode objectz")
        assert 0==status
        
        # run dvipng to convert image to a png file
        status = os.system('convert -density 300  objectz.pdf -quality 90  objectz.png')
        assert 0==status

        # copy the image to the final directory
        os.chdir(curpath)
        imagepath = os.path.join(os.path.abspath(self.imagedir),'circuits')
        if not os.path.exists(imagepath):
            os.makedirs(imagepath)
        print("Copying file to ", imagepath, outfn)
        shutil.copyfile(os.path.join(tempdir, "objectz.png"), outfn)
        #shutil.rmtree(tempdir)
        return relfn, outfn

    def wrap_text(self):
        latex_class = 'article'
        objectzscript = self.text
        font_size = self.font_size
        text = """
\\documentclass[preview]{standalone}
\\usepackage{oz}
\\pagestyle{empty}
\\begin{document}
%(objectzscript)s
\\end{document}""" % locals()

        # write script out to build file
        f = open('objectz.tex','w')
        f.write(text)
        f.close()

class Pylit_ozError(SphinxError):
    category = 'Pylit-oz error'

class pylit_oz(nodes.General, nodes.Element):
    pass

class Pylit_oz(Directive):

    has_content = True
    required_arguments = 0
    optional_arguments = 1
    final_argument_whitespace = True
    option_spec = {
        'label': directives.unchanged,
        'name': directives.unchanged,
        'nowrap': directives.flag,
        'width': directives.unchanged,
        'align': directives.unchanged,
    }

    def run(self):
        latex = '\n'.join(self.content)
        node = pylit_oz()
        node['latex'] = latex
        node['label'] = None
        node['docname'] = self.state.document.settings.env.docname
        style = ''
        if 'width' in self.options:
            style += 'width=%s' % self.options['width']
        if 'align' in self.options:
            style += ' class="align-%s"' % self.options['align']
        node['style'] = style
        ret = [node]
        set_source_info(self,node)
        return ret

def html_visit_pylit_oz(self, node):
    latex = node['latex']
    try: 
        imagedir = self.builder.imgpath
        fname, relfn  = RenderOzImage(latex,self.builder).render()
        print("rendered image:",fname)
    except OzExtError as exc:
        msg = unicode(str(exc), 'utf-8', 'replace')
        sm = nodes.system.message(msg, type='WARNING', level=2,
            backrefs=[], source=node['latex'])
        raise nodes.SkipNode
        sm.walkabout(self)
        self.builder.warn('display latex %r: ' % node['latex'] + str(exc))
        raise nodes.SkipNode
    if fname is None:
        self.body.append('<span class="Oz">%s</span>' %
                self.encode(node['latex']).strip())
    else:
        c = ('<img src="%s" %s' % (fname,node['style']))
        self.body.append(c + '/>')
    raise nodes.SkipNode

def latex_visit_pylit_oz(self, node):
    self.body.append('$' + node['latex'] + '$')
    raise nodes.SkipNode

def setup(app):
    app.add_node(pylit_oz,
            html = (html_visit_pylit_oz, None),
            latex = (latex_visit_pylit_oz, None),
    )
    app.add_directive('pylit-oz', Pylit_oz)

