all: shell
	gcc shell.o -o shell

shell: shell.c
	gcc -c shell.c -o shell.o

clean:
	rm -f shell *.o
