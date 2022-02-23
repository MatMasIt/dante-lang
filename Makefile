.PHONY: help
.PHONY: all bin windows64 windows32 linux64 linux32 linuxstatic64 linuxstatic32
RED := '\033[0;31m'
NC := '\033[0m'
GREEN := '\033[0;32m'
BLUE := '\033[0;34m'
.DEFAULT_GOAL := help
SHELL := /bin/bash
OS := $(shell lsb_release -si)
ifneq (, $(shell which doas))
	RP := "doas"
else
	RP := "sudo"
endif
# $TESTFILE is loaded from .env, it is the path to the target dante program
ifneq (,$(wildcard ./.env))
    include .env
    export
endif
setup: ## Prepare all dependencies
	@printf $(NC)"Installing dependencies for"$(BLUE)" "$(OS)" "$(NC)"...\n" | ts '[%Y-%m-%d %H:%M:%S]'
ifeq ($(OS), $(shell echo "Ubuntu"))
	$(RP) apt install gcc gcc-multilib g++-multilib mingw-w64 valgrind
else ifeq ($(OS),"Debian")
	$(RP) apt install gcc gcc-multilib g++-multilib mingw-w64 valgrind
else ifeq ($(OS),"Arch")
	$(RP) pacman -S gcc mingw-w64-gcc valgrind
else ifeq ($(OS),"Artix")
	$(RP) pacman -S gcc mingw-w64-gcc valgrindendif
else ifeq ($(OS),"Fedora")
	$(RP) yum install gcc gcc-c++ mingw64-gcc mingw32-cpp mingw64-cpp mingw32-gcc valgrind
else ifeq ($(OS),"Void")
	$(RP) xbps-install gcc gcc-c++ cross-i686-w64-mingw32 cross-x86_64-w64-mingw32 valgrind
else ifeq ($(OS),"Gentoo")
	$(RP) emerge-pb sys-devel/gcc sys-devel/crossdev dev-util/valgrind
endif
all: ## Makes all binaries
	@make -s bin
bin: ## Make linux and windows binaries
	@date +%s%N | cut -b1-13 > .timebin
	@printf $(NC)"Compiling"$(BLUE)" all targets"$(NC)"...\n" | ts '[%Y-%m-%d %H:%M:%S]'
	@make -s linux64
	@make -s linux32
	@make -s linuxstatic64
	@make -s  linuxstatic32
	@make -s windows32
	@make -s windows64
	@printf "Outputting "$(BLUE)"TOC file"$(NC)"\n" | ts '[%Y-%m-%d %H:%M:%S]'
	@file bin/* | grep -v ".log" > bin/filestoc.txt 2>&1
	@printf "Done, took a total of " | ts '[%Y-%m-%d %H:%M:%S]'
	@echo "scale=3;$$(($$(date +%s%N | cut -b1-13)-$$(cat .timebin))) / 1000" | bc -l | xargs -I {} echo {} "s" 
	@rm .timebin
windows64: ## Make windows 64 bit binary
	@date +%s%N | cut -b1-13 > .timepart
	@mkdir -p bin
	@printf "Compiling"$(BLUE)" windows64"$(NC)"\n"  | ts '[%Y-%m-%d %H:%M:%S]'
	@x86_64-w64-mingw32-gcc-win32 Dante.cpp -m64 -o bin/dante64.exe -static -lstdc++ > bin/windows64.log 2>&1 &&\
	printf $(GREEN)"Compiled successfully "$(NC)"in " | ts '[%Y-%m-%d %H:%M:%S]' &&\
	echo "scale=3;$$(($$(date +%s%N | cut -b1-13)-$$(cat .timepart))) / 1000" | bc -l | xargs -I {} echo {} "s"   && \
	rm .timepart ||\
	printf $(RED)"Compilation error:"$(NC)" check logs\nIs mingw installed?\n Try "$(GREEN)"make setup"$(NC) | ts '[%Y-%m-%d %H:%M:%S]'
windows32: ## Make windows 32 bit binary
	@date +%s%N | cut -b1-13 > .timepart
	@mkdir -p bin
	@printf "Compiling"$(BLUE)" windows32"$(NC)"\n"  | ts '[%Y-%m-%d %H:%M:%S]'
	@i686-w64-mingw32-g++ Dante.cpp  -o bin/dante32.exe -static -lstdc++ > bin/windows32.log 2>&1 &&\
	printf $(GREEN)"Compiled successfully "$(NC)"in " | ts '[%Y-%m-%d %H:%M:%S]' &&\
	echo "scale=3;$$(($$(date +%s%N | cut -b1-13)-$$(cat .timepart))) / 1000" | bc -l | xargs -I {} echo {} "s" && \
	rm .timepart ||\
	printf $(RED)"Compilation error:"$(NC)" check logs\nIs mingw 32 bit support installed?\n Try "$(GREEN)"make setup"$(NC)"\n" | ts '[%Y-%m-%d %H:%M:%S]'
linux64: ## Make linux 64 bit  binary
	@date +%s%N | cut -b1-13 > .timepart
	@mkdir -p bin
	@printf "Compiling"$(BLUE)" linux64"$(NC)"\n" | ts '[%Y-%m-%d %H:%M:%S]'
	@g++ Dante.cpp -o bin/dante64.o -g > bin/linux64.log 2>&1 && \
	printf $(GREEN)"Compiled successfully "$(NC)"in " | ts '[%Y-%m-%d %H:%M:%S]' && \
	echo "scale=3;$$(($$(date +%s%N | cut -b1-13)-$$(cat .timepart))) / 1000" | bc -l | xargs -I {} echo {} "s" && \
	rm .timepart || \
	printf $(RED)"Compilation error:"$(NC)" check logs\nIs gcc installed?\nTry "$(GREEN)"make setup"$(NC)"\n"  | ts '[%Y-%m-%d %H:%M:%S]'
linux32: ## Make linux 64 bit binary
	@date +%s%N | cut -b1-13 > .timepart
	@mkdir -p bin
	@printf "Compiling"$(BLUE)" linux32"$(NC)"\n" | ts '[%Y-%m-%d %H:%M:%S]'
	@g++ Dante.cpp -m32 -o bin/dante32.o -g > bin/linux32.log 2>&1 &&\
	printf $(GREEN)"Compiled successfully "$(NC)"in " | ts '[%Y-%m-%d %H:%M:%S]' &&\
	echo "scale=3;$$(($$(date +%s%N | cut -b1-13)-$$(cat .timepart))) / 1000" | bc -l | xargs -I {} echo {} "s"  &&\
	rm .timepart ||\
	printf $(RED)"Compilation error:"$(NC)" check logs\nIs gcc 32 bit support installed?\nTry "$(GREEN)"make setup"$(NC)"\n"  | ts '[%Y-%m-%d %H:%M:%S]'
linuxstatic64: ## Make static linux 64 bit binary
	@date +%s%N | cut -b1-13 > .timepart
	@mkdir -p bin
	@printf "Compiling"$(BLUE)" linux64 (static)"$(NC)"\n" | ts '[%Y-%m-%d %H:%M:%S]'
	@g++ Dante.cpp -m64 -o bin/dante64.static.o -g -static > bin/linuxstatic64.log 2>&1 && \
	printf $(GREEN)"Compiled successfully "$(NC)"in " | ts '[%Y-%m-%d %H:%M:%S]' && \
	echo "scale=3;$$(($$(date +%s%N | cut -b1-13)-$$(cat .timepart))) / 1000" | bc -l | xargs -I {} echo {} "s" && \
	rm .timepart || \
	printf $(RED)"Compilation error:"$(NC)" check logs\nIs gcc installed?\nTry "$(GREEN)"make setup"$(NC)"\n"  | ts '[%Y-%m-%d %H:%M:%S]'
linuxstatic32: ## Make static linux 32 bit binary
	@date +%s%N | cut -b1-13 > .timepart
	@mkdir -p bin
	@printf "Compiling"$(BLUE)" linux32 (static)"$(NC)"\n" | ts '[%Y-%m-%d %H:%M:%S]'
	@g++ Dante.cpp -m32 -o bin/dante32.static.o -g -static > bin/linuxstatic32.log 2>&1 && \
	printf $(GREEN)"Compiled successfully "$(NC)"in " | ts '[%Y-%m-%d %H:%M:%S]' && \
	echo "scale=3;$$(($$(date +%s%N | cut -b1-13)-$$(cat .timepart))) / 1000" | bc -l | xargs -I {} echo {} "s"  && \
	rm .timepart || \
	printf $(RED)"Compilation error:"$(NC)" check logs\nIs gcc 32 bit support installed?\nTry "$(GREEN)"make setup"$(NC)"\n"  | ts '[%Y-%m-%d %H:%M:%S]'
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
