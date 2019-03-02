// source: https://www.geeksforgeeks.org/getopt-function-in-c-to-parse-command-line-arguments/
// Program to illustrate the getopt() 
// function in C 
  
#include <stdio.h>  
#include <unistd.h>  
#include <getopt.h>
  
// test with:
// ./a.out in.csv in2.csv -n 3 -o out.csv -b -x
int main(int argc, char *argv[])  
{ 
    int opt;  
    while((opt = getopt(argc, argv, "n:o:b")) != -1)  
    {  
        switch(opt)  
        {  
            case 'n':  
            case 'o':  
            case 'b':  
                printf("option: %c, value: %s\n", opt, optarg);  
                break;  
            case ':':   
                printf("option %c needs a value\n", optopt);  
                break;  
            case '?':   
                printf("unknown option: %c\n", optopt); 
                break;  
        }  
    }  
      
    // optind is for the extra arguments 
    // which are not parsed 
    for(; optind < argc; optind++){      
        printf("extra arguments: %s\n", argv[optind]);  
    } 
      
    return 0;  
} 