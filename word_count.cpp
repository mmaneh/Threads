#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

const int MaxThreads = 5;

typedef struct {
    int thread_id;
    int line_number;
    char* line_data;
    int word_count;
} ThreadData;


int global_max_words = 0;
int max_thread_id = -1;
int max_line_number = -1;
pthread_mutex_t max_mutex = PTHREAD_MUTEX_INITIALIZER;


void* process_line(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    data->word_count = 0;

    char* ptr = data->line_data;
    int in_word = 0;

    while (*ptr) {
        if (*ptr != ' ' && *ptr != '\t' && *ptr != '\n') {
            if (!in_word) {
                data->word_count++;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
        ptr++;
    }

    printf("Thread %d processed line %d: %d words\n", data->thread_id, data->line_number, data->word_count);

    
    pthread_mutex_lock(&max_mutex);
    if (data->word_count > global_max_words) {
        global_max_words = data->word_count;
        max_thread_id = data->thread_id;
        max_line_number = data->line_number;
    }
    pthread_mutex_unlock(&max_mutex);

    return NULL;
}
