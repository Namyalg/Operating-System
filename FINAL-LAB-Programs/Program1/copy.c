#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#define BUF_SIZE 8000

//fcntl has all the file related utilities
//open, close
//read and write present in unistd.h

int main(int argc, char* argv[]) { 
    int input_fd, output_fd; 
    ssize_t ret_in, ret_out; 
    char buffer[BUF_SIZE];

    //check for 3 command arguments 
    if(argc != 3){
        printf ("Not enough arguments to support copy!");
        return 1;
    }

    //read using command line arguments
    input_fd = open (argv [1], O_RDONLY);
    if (input_fd == -1) {
        perror ("open");
        return 2;
    }

    //O_CREAT - create a file if doesnt exist
    //O_EXCL - prevent creation if it exists
    //as the file needs to be copied

    //user-group-others
    //
    //read-write-execute =====> thats how the permissions are given
    //
    output_fd = open(argv[2], O_WRONLY | O_CREAT |O_EXCL, 777);
    if(output_fd == -1){
        perror("open");
        return 3;
    }

    //the process of copy is basically writing from one file to another at a different location
    
    while((ret_in = read (input_fd, &buffer, BUF_SIZE)) > 0){
        ret_out = write (output_fd, &buffer, (ssize_t) ret_in);
        if(ret_out != ret_in){
            perror("write");
            return 4;
            }
    }

    close (input_fd);
    close (output_fd);
    return (0);
}
