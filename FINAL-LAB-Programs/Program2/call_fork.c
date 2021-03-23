#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>


//fork needs sys/types and unistd.h
//only call that returns 2 values
//exhibited as copy on write, i.e only if a change is created then copied
//dirty bit is used to determine the same

//stack and variables are different for both of them

//the exec family of functions is used to replace the exisitng code with another process
//only if fails returns an error, else never return control back

//FORK USES COPY ON WRITE TECHNIQUE     
int main(int argc, char* argv[]){
    if(fork() == 0){
        printf("In the child\n");
        printf("Process id of child is : %d\n", getgid());
        printf("Parent process id of child is : %d\n", getppid());

        //using execl to execute another piece of code
        execl("./cipher", "ceaser_cipher.c", argv[1], argv[2], NULL);
        exit(0);
    }
    else{
        wait(NULL);
        printf("In the parent\n");
        printf("Process id of parent is : %d\n", getgid());
        printf("Parent process id of parent is : %d\n", getppid());
    }
    
}