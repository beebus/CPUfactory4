LINT		:= cpplint
LINTFLAGS	:= --repository=. --recursive --extensions=cpp,h --quiet
LINTFLAGS	+= --filter=-build/include_subdir

.PHONY: lint 
lint:	$(SRCS) $(HDRS) ## Run cpp lint over project files
	@$(LINT) $(LINTFLAGS) include lib src

