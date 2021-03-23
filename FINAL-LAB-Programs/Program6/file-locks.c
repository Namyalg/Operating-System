#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
 
int main(int argc, const char *argv[]){
    int fd;
    char buffer[255] = "";
    struct flock fvar;
    if(argc == 1){
        printf("usage: %s filename\n", argv[0]);
    }
    if((fd = open(argv[1], O_RDWR)) == -1){
        perror("open");
        exit(1);
    }

    //type is write lock
    fvar.l_type = F_WRLCK;
    fvar.l_whence = SEEK_END;
    fvar.l_start = SEEK_END - 100;
    fvar.l_len = 100;
    printf("trying to get lock...\n");

    //if setlock fails, it means another process has acquired the lock
    while((fcntl(fd, F_SETLK, &fvar)) == -1){
        fcntl(fd, F_GETLK, &fvar);
        printf("\nFile already locked by process (pid): \t%d\n",fvar.l_pid);
    }
    printf("locked\n");

    //try to get from end of file
    if((lseek(fd, SEEK_END - 50, SEEK_END)) == -1){
        perror("lseek");
        exit(1);
    }

    //print the process using the file lock
    printf("The process using it is %d \n", fvar.l_pid);
    if((read(fd, buffer, 100)) == -1){
        perror("read");
        exit(1);
    }
    printf("The process id is %d ", getpid());
    printf("data read from file.. \n");
    puts(buffer);
    printf("press enter to release lock\n");
    getchar();

    //unlock the file
    fvar.l_type = F_UNLCK;
    fvar.l_whence = SEEK_SET;
    fvar.l_start = 0;
    fvar.l_len = 0
    if((fcntl(fd,F_UNLCK,&fvar))==-1){
        perror("fcntl");
        exit(0);
    }
    printf("Unlocked\n");
    close(fd);
    return 0;
}
