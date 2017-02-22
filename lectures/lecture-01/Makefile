all:
	gcc -c -g *.c src/*.c -std=c11 -Werror -Wall -pedantic-errors -I./include
	gcc *.o -o a.out
	rm *.o
	gnome-terminal --tab -e "/bin/bash -c 'valgrind --leak-check=yes ./a.out; exec /bin/bash -i'"