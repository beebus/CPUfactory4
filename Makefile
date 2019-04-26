.PHONY: deps
deps:
	./scripts/install.sh

.PHONY: build
	cd deps/glui && make
	cd deps/g3log && make
