.PHONY: inc-major
inc-major:	## increment major verison number
	@python $(MK)/pyversion.py major

.PHONY: inc-minor
inc-minor:	## increment minor verison number
	@python $(MK)/pyversion.py minor

.PHONY: inc-build
inc-build:	## increment build verison number
	@python $(MK)/pyversion.py build

.PHONY:	version
version: ## display current version number
	@python $(MK)/pyversion.py version
