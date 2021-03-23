#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#define BUFFER 100000
//./a.out is the value given to argv[0]
//there are 2 arguments in this 

//run with ./rm and then pass the file to be removed

int main(int argc, char* argv[]){
    char content[BUFFER];

    //using the unlink command, a single file, is removed

    //printf("%s\n", argv[1]);
    //printf("%d", argc);
    if(argc != 2){
        printf("Not enough arguments passed\n");
        return 0;
    }
    //open, read, write and close
    FILE *fptr;
    int fopen;
    fopen = open(argv[1], O_RDWR);
    if(fopen == -1){
        printf("File in non-existent\n");
        return 1;
    }
    else{
        int dltfile;
        dltfile = unlink(argv[1]);
        printf("%d", dltfile);
        if(dltfile == -1){
            perror("Unlink Error\n");
            return 3;
        }
    }
    //argv[0] -> command
    //argv[1] -> source
    //argv[2] -> destination
    //open the file , if returns a negative number then call fails

    return 0;
}
