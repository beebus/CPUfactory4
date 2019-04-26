.PHONY: deps
deps:
	./scripts/install.sh

.PHONY: build
build:
	cd deps/glui && make
	cd deps/g3log && make
