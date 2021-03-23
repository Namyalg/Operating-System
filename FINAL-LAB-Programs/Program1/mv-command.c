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
/*
A symbolic or soft link is an actual link to the original file, 
whereas a hard link is a mirror copy of the original file. If you delete the original file, 
the soft link has no value, because it points to a non-existent file. But in the case of hard link, 
it is entirely opposite. Even if you delete the original file, the hard link will still has the data of the 
original file. Because hard link acts as a mirror copy of the original file.

//in hardlink the same inode number is shared, but in soft link it is di



HARD LINK CREATES A COPY OF A FILE
SOFT LINK IS AN ALIAS NAME THATS IT

*/

//the logic used here is that, the file in unlinked to its current location
//it is linked to the location it has to be moved to
int main(int argc, char* argv[]){
    char content[BUFFER];
    if(argc != 3){
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

    //FIRST LINK AND THEN UNLINK WITH CURRENT LOCATION

    int mv_;

    //creates a hard link, i.e another entity with same contents
    //is different from copying as the contents are updated in both places simultaneously
    
    //it points to a different inode numebr
    mv_ = link(argv[1], argv[2]);
    if(mv_ == -1){
        perror("Link error");
        return 3;
    }
    int dlt_;
    dlt_ = unlink(argv[1]);
    if(dlt_ == -1){
        printf("Unlink error");
        return 4;
    }

    //argv[0] -> command
    //argv[1] -> source
    //argv[2] -> destination
    //open the file , if returns a negative number then call fails

    return 0;
}
