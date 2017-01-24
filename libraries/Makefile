static:
	gcc staticlib/*.c -c
	ar rcs libstaticlib.a *.o
	rm *.o

dynamic:
	gcc -fPIC -c staticlib/*.c
	gcc -shared -o libdynamic.so *.o
	rm *.o

all:
	gcc main.c -c -I ./staticlib 
	gcc *.o -L . -lstaticlib
	rm *.o

main-dyn:
	gcc main-dyn.c -c
	gcc *.o -ldl
	rm *.o