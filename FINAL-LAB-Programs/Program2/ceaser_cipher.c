#include<stdio.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>

//this is the utility code that is run, this is used to decrypt a message

int main(int argc, char* argv[]){
    char string[1000];
    int arguments = argc;
    if (arguments != 3){
        printf("Not enough arguments \n");
        exit(0);
    }
    else{
        int key = atoi(argv[2]);
        char lower_letters[] = {' ' ,'a', 'b', 'c', 'd' ,'e', 'f' ,'g' ,'h', 'i', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's' , 't', 'u', 'v', 'w', 'x', 'y','z'};
        char upper_letters[] = { ' ', 'A', 'B', 'C', 'D' ,'E', 'F' ,'G' ,'H', 'I', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S' , 'T', 'U', 'V', 'W', 'X', 'Y','Z'};
        strcpy(string, argv[1]);
        for(int i = 0; string[i] != '\0'; i++){
            int ascii;
            int val = string[i];
            if(val > 97 && val < 122){
                ascii = ((string[i] + key) - 97) % 26;
                string[i] = lower_letters[ascii];
            }
            else if(val > 65 && val < 90){
                ascii = ((string[i] + key) - 65) % 26;
                string[i] = upper_letters[ascii];
            }
        }
        printf("The encrypted message is : ");
        printf("%s\n", string);
    }
    return 0;    
}
