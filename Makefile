all:
	make linux
	make windows
windows:
	x86_64-w64-mingw32-gcc-win32 Dante.cpp -o bin/dante64.exe -static -lstdc++
linux:
	g++ Dante.cpp -o bin/dante.o -g
valgrind:
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./dante l
gdb:
	gdb -ex=r --args dante esempi/se.dante
