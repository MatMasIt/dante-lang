.PHONY: help
.PHONY: all bin windows64 windows32 linux64 linux32 linuxstatic64 linuxstatic32
RED := '\033[0;31m'
NC := '\033[0m'
GREEN := '\033[0;32m'
BLUE := '\033[0;34m'
.DEFAULT_GOAL := help
SHELL := /bin/bash
# $TESTFILE is loaded from .env, it is the path to the target dante program
ifneq (,$(wildcard ./.env))
    include .env
    export
endif
all: ## Makes all binaries
	@make -s bin
bin: ## Make linux and windows binaries
	@date +%s%N | cut -b1-13 > .timebin
	@printf $(NC)"Compiling"$(BLUE)" all targets"$(NC)"...\n"
	@make -s linux64
	@make -s linux32
	@make -s linuxstatic64
	@make -s  linuxstatic32
	@make -s windows32
	@make -s windows64
	@printf "Outputting "$(BLUE)"TOC file\n"$(NC)
	@file bin/* | grep -v ".log" > bin/filestoc.txt 2>&1
	@printf "Done, took a total of "
	@echo "scale=3;$$(($$(date +%s%N | cut -b1-13)-$$(cat .timebin))) / 1000" | bc -l | xargs -I {} echo {} "s"
	@rm .timebin
windows64: ## Make windows 64 bit binary
	@date +%s%N | cut -b1-13 > .timepart
	@mkdir -p bin
	@printf "Compiling"$(BLUE)" windows64\n"$(NC)
	@x86_64-w64-mingw32-gcc-win32 Dante.cpp -m64 -o bin/dante64.exe -static -lstdc++ > bin/windows64.log 2>&1 &&\
	printf $(GREEN)"Compiled successfully "$(NC)"in " &&\
	echo "scale=3;$$(($$(date +%s%N | cut -b1-13)-$$(cat .timepart))) / 1000" | bc -l | xargs -I {} echo {} "s" && \
	rm .timepart ||\
	printf $(RED)"Compilation error:"$(NC)" check logs\n"
windows32: ## Make windows 32 bit binary
	@date +%s%N | cut -b1-13 > .timepart
	@mkdir -p bin
	@printf "Compiling"$(BLUE)" windows32\n"$(NC)
	@i686-w64-mingw32-g++ Dante.cpp  -o bin/dante32.exe -static -lstdc++ > bin/windows32.log 2>&1 &&\
	printf $(GREEN)"Compiled successfully "$(NC)"in " &&\
	echo "scale=3;$$(($$(date +%s%N | cut -b1-13)-$$(cat .timepart))) / 1000" | bc -l | xargs -I {} echo {} "s" && \
	rm .timepart ||\
	printf $(RED)"Compilation error:"$(NC)" check logs\n"
linux64: ## Make linux 64 bit  binary
	@date +%s%N | cut -b1-13 > .timepart
	@mkdir -p bin
	@printf "Compiling"$(BLUE)" linux64\n"$(NC)
	@g++ Dante.cpp -o bin/dante64.o -g > bin/linux64.log 2>&1 && \
	printf $(GREEN)"Compiled successfully "$(NC)"in " && \
	echo "scale=3;$$(($$(date +%s%N | cut -b1-13)-$$(cat .timepart))) / 1000" | bc -l | xargs -I {} echo {} "s" && \
	rm .timepart || \
	printf $(RED)"Compilation error:"$(NC)" check logs\n"
linux32: ## Make linux 64 bit binary
	@date +%s%N | cut -b1-13 > .timepart
	@mkdir -p bin
	@printf "Compiling"$(BLUE)" linux32\n"$(NC)
	@g++ Dante.cpp -m32 -o bin/dante32.o -g > bin/linux32.log 2>&1 &&\
	printf $(GREEN)"Compiled successfully "$(NC)"in " &&\
	echo "scale=3;$$(($$(date +%s%N | cut -b1-13)-$$(cat .timepart))) / 1000" | bc -l | xargs -I {} echo {} "s" &&\
	rm .timepart ||\
	printf $(RED)"Compilation error:"$(NC)" check logs\n"
linuxstatic64: ## Make static linux 64 bit binary
	@date +%s%N | cut -b1-13 > .timepart
	@mkdir -p bin
	@printf "Compiling"$(BLUE)" linux64 (static)\n"$(NC)
	@g++ Dante.cpp -m64 -o bin/dante.static64.o -g -static > bin/linuxstatic64.log 2>&1 && \
	printf $(GREEN)"Compiled successfully "$(NC)"in " && \
	echo "scale=3;$$(($$(date +%s%N | cut -b1-13)-$$(cat .timepart))) / 1000" | bc -l | xargs -I {} echo {} "s" && \
	rm .timepart || \
	printf $(RED)"Compilation error:"$(NC)" check logs\n"
linuxstatic32: ## Make static linux 32 bit binary
	@date +%s%N | cut -b1-13 > .timepart
	@mkdir -p bin
	@printf "Compiling"$(BLUE)" linux32 (static)\n"$(NC)
	@g++ Dante.cpp -m32 -o bin/dante.static32.o -g -static > bin/linuxstatic32.log 2>&1 && \
	printf $(GREEN)"Compiled successfully "$(NC)"in " && \
	echo "scale=3;$$(($$(date +%s%N | cut -b1-13)-$$(cat .timepart))) / 1000" | bc -l | xargs -I {} echo {} "s" && \
	rm .timepart || \
	printf $(RED)"Compilation error:"$(NC)" check logs\n"
valgrind: ## RUN valgrind in $TESTFILE
	@valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./bin/dante.o "${TESTFILE}"
gdb: ## Run $TESTFILE in linux 
	@gdb -ex=r --args ./bin/dante.o "${TESTFILE}"
linr: ## Run $TESFILE in linux
	@./bin/dante64.o "${TESTFILE}"
wine: ## Run $TESTFILE in dante64.exe, through wine emulation
	@wine64 ./bin/dante64.exe "${TESTFILE}"
help: ## Default action, this page
	@echo "The Dante Interpreter"
	@grep ': ## ' Makefile | grep -v "@grep" | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
# Self documenting makefile, see https://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
