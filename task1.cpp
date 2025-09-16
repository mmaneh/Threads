#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
typedef struct {
    int* arr;
    int size;
}Array;

void* sum(void * arg) {
    Array* data = (Array*) arg;
    int res = 0;
    for (int i = 0; i < data->size; ++i) {
        res += data->arr[i];
    }  
    printf("%d", res);
    return NULL;
}
int main() {
    pthread_t t1;

    int arr[]= {1,2,3,4,5};
    Array data = {arr,5};
    pthread_create(&t1, NULL, sum, &data); 

    pthread_join(t1,NULL);

    return 0;
}
