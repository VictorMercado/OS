#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Define a struct to hold the arguments for the thread function
struct ThreadArgs {
    int arg1;
    float arg2;
    char arg3;
    bool arg4;
};

// Thread function that takes multiple arguments
void* threadFunction(void* arg) {
    // Cast the argument back to the correct type
    struct ThreadArgs* args = (struct ThreadArgs*)arg;

    // Access the arguments
    // printf("arg1: %d\n", args->arg1);
    // printf("arg2: %f\n", args->arg2);
    // printf("arg3: %c\n", args->arg3);
    for (int i=0;i<10;i++) {
      if (args->arg4) {
        printf("thread3: adding to arg1\n");
      } else {
        printf("adding to arg1\n");
      }
      args->arg1++;
    }
    printf("printing from threadFucntion: %d\n", args->arg1);

    return NULL;
}
void* threadFunction2(void* arg) {
    // Cast the argument back to the correct type
    struct ThreadArgs* args = (struct ThreadArgs*)arg;

    // Access the arguments
    // printf("arg1: %d\n", args->arg1);
    // printf("arg2: %f\n", args->arg2);
    // printf("arg3: %c\n", args->arg3);
    for (int i=0;i<10;i++) {
      printf("adding to arg2 \n");
      args->arg2 = args->arg2 + 1.0f;
    } 
    printf("printing from threadFunction2: %f\n", args->arg2);

    return NULL;
}



int main() {
    pthread_t thread;
    pthread_t thread2;
    pthread_t thread3;
    int result;

    // Create a struct to hold the arguments
    struct ThreadArgs args = {1, 1.00, 'A'};

    // Create a new thread and pass the struct as the argument
    result = pthread_create(&thread2, NULL, threadFunction, (void*)&args);
    if (result != 0) {
        fprintf(stderr, "Error creating thread: %d\n", result);
        exit(EXIT_FAILURE);
    }
    result = pthread_create(&thread, NULL, threadFunction2, (void*)&args);
    if (result != 0) {
        fprintf(stderr, "Error creating thread: %d\n", result);
        exit(EXIT_FAILURE);
    }
    args.arg4 = true;
    result = pthread_create(&thread3, NULL, threadFunction, (void*)&args);
    if (result != 0) {
        fprintf(stderr, "Error creating thread: %d\n", result);
        exit(EXIT_FAILURE);
    }
    // Wait for the thread to finish
    result = pthread_join(thread2, NULL);
    result = pthread_join(thread, NULL);
    result = pthread_join(thread3, NULL);
    if (result != 0) {
        fprintf(stderr, "Error joining thread: %d\n", result);
        exit(EXIT_FAILURE);
    }

    printf("Thread has finished\n");

    return 0;
}
