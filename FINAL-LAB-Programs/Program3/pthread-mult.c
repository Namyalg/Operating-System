#include<sys/wait.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
int product[4];
int ind = 0;

//Threads are a path on program execution
//They operte in the same memory space and have registers, stack and pc independently
//the other resources are shared
//usually indenpendent lightweight combine to generate resultant
//pthreads are user level threads

void *find_product (void* i){
        int *myid = (int *)i;
        int prod = 1;
        int val = *myid;
        int start = val * 5;
        int end = start + 5;
        for(int j = start+1; j <= end; j++){
            prod = prod * j;
        }
        printf("Product from %d to %d is %d \n", start, end, prod);
        product[ind++] = prod;
        return i;
}
 
int main() {
    //each executing parallely
    pthread_t tid[10];
    //to get the product of humbers from 0 to 25
    int final_product = 1;
    //the process of mult is carried out in each thread
    for (int i = 0; i < 5; i++){
        pthread_create(&tid[i], NULL, find_product, ((void *)&i));
        pthread_join(tid[i], NULL); 
    }
    for(int i = 0; i < 5; i++){
        final_product = final_product * product[i];
    }
    printf("The product is %d ", final_product);
    //pthread_exit(NULL);
    return(0);
}

