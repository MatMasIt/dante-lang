.PHONY: help
.DEFAULT_GOAL := help
# $TESTFILE is loaded from .env, it is the path to the target dante program
ifneq (,$(wildcard ./.env))
    include .env
    export
endif
all: ## Makes all binaries
	make bin
bin: ## Make linux and windows binaries
	make linux
	make windows
windows: ## Make windows binary
	mkdir -p bin
	x86_64-w64-mingw32-gcc-win32 Dante.cpp -o bin/dante64.exe -static -lstdc++
linux: ## Make linux binary
	mkdir -p bin
	g++ Dante.cpp -o bin/dante.o -g
valgrind: ## RUN valgrind in $TESTFILE
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./bin/dante.o "${TESTFILE}"
gdb: ## Run $TESTFILE in linux 
	gdb -ex=r --args ./bin/dante.o "${TESTFILE}"
linr: ## Run $TESFILE in linux
	./bin/dante.o "${TESTFILE}"
wine: ## Run $TESTFILE in dante64.exe, through wine emulation
	wine64 ./bin/dante64.exe "${TESTFILE}"
help: ## Default action, this page
	@echo "The Dante Interpreter"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' Makefile | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
# Self documenting makefile, see https://marmelab.com/blog/2016/02/29/auto-documented-makefile.html