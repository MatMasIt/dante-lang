all:
	gcc dante.c -o dante -g 2>&1 | tee  build.log
