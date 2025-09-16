#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
typedef struct {
    int* arr;
    int count;
}Array;

bool isPrime(int N) {
    if ( N < 2) return false;
    for (int i = 2; i * i <= N ; ++i) {
        if (N % i == 0) return false;
    }
    return true;
}
void* fillArray(void* arg) {
    int N = *(int*)arg;
    int count = 0;
    for (int i = 2; i < N; ++i) {
        if (isPrime(i)) {
            ++count;
        }
    }
    int* arr = (int*)malloc(count * sizeof(int));
    int j = 0;
    for (int i = 2; i < N; ++i) {
        if (isPrime(i)) arr[j++] = i;
    }
    Array * data = (Array* )malloc(sizeof(Array));
    data->arr = arr;
    data->count = count;
    return data;
}

void* printAndfree(void* arg) {
    Array * data = (Array*) arg;
    for (int i = 0; i < data->count;++i) {
        printf("%d",data->arr[i]);
    }
    free(data->arr);
    free(data);
    return NULL;
}

int main() {
    int N;
    scanf("%d", &N);

    pthread_t t1, t2;
    void* res;

    pthread_create(&t1, NULL, fillArray, &N);
    pthread_join(t1, &res);

    pthread_create(&t2, NULL, printAndfree, res);
    pthread_join(t2,NULL);
}
