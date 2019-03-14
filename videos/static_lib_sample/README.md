# Contents

1. Create **C module**
    1. separate interface and implementation
    2. create module files
    3. compile multiple files (`gcc main.c vector2.c extra.c -lm` or `gcc *.c -lm`)
2. Create static library with **gcc** and **ar** (Linux)
    1. move modules to separate `mygraphics` folder
    2. compile library with gcc (`gcc -c vector2.c extra.c`)
    3. archive library files with ar (`ar rcs libmygraphics.a vector2.o extra.o`)
    4. compile program with created library (`gcc main.c -lmygraphics`)
        1. specify directory to include library .h files (`-I`)
        2. specify library (`-lmygraphics`) and directory path (`-L`)
           `gcc main.c -I../mygraphics -L../mygraphics/lib -lmygraphics -lm`
3. Create static library with **CMake** and **make** (Linux)
    1. install cmake (`sudo apt install cmake`)
    2. configure library CMake project
    3. configure program CMake project
