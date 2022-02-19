all:
	g++ Dante.cpp -o dante -g
valgrind:
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./dante l
gdb:
	gdb -ex=r --args dante esempi/se.dante
