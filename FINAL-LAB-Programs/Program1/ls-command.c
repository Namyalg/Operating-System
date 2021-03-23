#include<stdio.h> 
#include<dirent.h> 
#include<sys/stat.h> 
#include<pwd.h> 
#include<grp.h> 
#include<time.h> 

int main(){
    DIR *directory;
    directory = opendir(".");
    struct dirent *read_dir;
    struct stat buf;
    char P[10] = "rwxrwxrwx";
    char AP[10] = " ";
    int i, j;
    struct tm *t; 
    char time[26];

    //getpwuid
    struct passwd *pswd; 
    
    //getgrid
    struct group *grp;
    //to come to the present directory    
    //readdir(directory);
    //readdir(directory);

    while((read_dir = readdir(directory)) != NULL){
         stat(read_dir->d_name , &buf);
         if(S_ISDIR(buf.st_mode)) 
            printf("d"); 
        else if(S_ISREG(buf.st_mode)) 
            printf("-"); 
        else if(S_ISCHR(buf.st_mode)) 
            printf("c"); 
        else if(S_ISBLK(buf.st_mode)) 
            printf("b"); 
        else if(S_ISLNK(buf.st_mode)) 
            printf("l"); 
        else if(S_ISFIFO(buf.st_mode)) 
            printf("p"); 
        else if(S_ISSOCK(buf.st_mode)) 
            printf("s"); 
            
        for( i = 0, j = (1 << 8); i < 9 ; i++, j >>= 1) 
            AP[i]= (buf.st_mode & j ) ? P[i] : '-' ; 
            //file permissions
            printf("%s",AP); 

            //number of hard links
            printf("%5d",buf.st_nlink); 

        //user id, that is who the user is
        //user identifier
        pswd = getpwuid(buf.st_uid); 
        printf(" %.8s  ",pswd -> pw_name); 
        
        //group identifier
        grp = getgrgid(buf.st_gid); 
        printf(" %-8.8s  ",grp -> gr_name);

        //size of file
        printf("%d  ", buf.st_size);
        //time of creation
        //t = localtime(&buf.st_mtime); 
        //strftime(time,sizeof(time),"%b %d %H:%M", t);  printf(" %s", time); 
        printf(" %s", ctime(&buf.st_mtime));  


        //name of file finally
        printf(" %s  ",read_dir -> d_name);
        printf("\n");
    }

    return(0);
}
//this command can be used directly at the command line as <stat name of file>


//the permissions goes as USER GROUP OTHERS

//each uses 3 bits 644 means 110 100 100
//this stands for             rw-r--r--
/*
struct stat {
	mode_t			st_mode;
	ino_t			st_ino;
	dev_t			st_dev;
	dev_t			st_rdev;
	nlink_t			st_nlink;
	uid_t			st_uid;
	gid_t			st_gid;
	off_t			st_size;
	struct timespec	st_atim;
	struct timespec	st_mtim;
	struct timespec st_ctim;
	blksize_t		st_blksize;
	blkcnt_t		st_blocks;
};

*/
