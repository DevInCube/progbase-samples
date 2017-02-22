all:
	gcc -c -g *.c -I./
	gcc *.o -o a.out
	rm *.o
	gnome-terminal --tab -e "/bin/bash -c 'valgrind --leak-check=yes ./a.out; exec /bin/bash -i'"  
