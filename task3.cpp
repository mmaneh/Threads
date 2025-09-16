#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct {
    int* arr;
    int size;
}Array;

void * sum(void * arg) {
    Array* data  = (Array*)arg;
    int sum = 0;

    for(int i = 0; i < data->size; ++i) {
        sum += data->arr[i];
    }
    printf("%d", sum);
    return NULL;
}
int main() {
    int arr[] = {1, 2,3,4,5};
    Array data = {arr,5};

    pid_t pid = fork();

    if (pid < 0) {
        perror("fail");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) {

        pthread_t t1;
        pthread_create(&t1, NULL, sum, &data);
        pthread_join(t1,NULL);


    }else {
        wait(NULL);
    }

}
