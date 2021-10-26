all:
	gcc dante.c -o dante
	./dante | tee out.c
	gcc out.c -o out -lm
	./out
