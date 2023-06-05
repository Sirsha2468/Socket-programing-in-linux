#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t readCondition, writeCondition;
int sharedResource = 0;
int readerCount = 0; // Reader is 0

void *reader(void *arg) {
    int readerId = *(int*)arg;
    
    pthread_mutex_lock(&mutex);
    readerCount++;
    
    if (readerCount == 1) {
        // First reader, block writers
        pthread_mutex_lock(&writeCondition);
    }
    
    pthread_mutex_unlock(&mutex);
    
    // Read the shared resource
    printf("Reader %d reads: %d\n", readerId, sharedResource);
    
    pthread_mutex_lock(&mutex);
    readerCount--;
    
    if (readerCount == 0) {
        // Last reader, wake up writers
        pthread_mutex_unlock(&writeCondition);
    }
    
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

void *writer(void *arg) {
    int writerId = *(int*)arg;
    
    pthread_mutex_lock(&writeCondition);
    
    // Write to the shared resource
    sharedResource++;
    printf("Writer %d writes: %d\n", writerId, sharedResource);
    
    pthread_mutex_unlock(&writeCondition);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t readers[5], writers[5];
    int readerIds[5], writerIds[5];
    
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&readCondition, NULL);
    pthread_cond_init(&writeCondition, NULL);
    
    for (int i = 0; i < 5; i++) {
        readerIds[i] = i + 1;
        writerIds[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIds[i]);
        pthread_create(&writers[i], NULL, writer, &writerIds[i]);
    }
    
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&readCondition);
    pthread_cond_destroy(&writeCondition);
    
    return 0;
}
