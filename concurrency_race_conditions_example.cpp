//
//  concurrency_deadlock_example.cpp
//  
//
//  Created by Matthew Richardson on 12/5/16.
//
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int sharedResource = 0;

void *thread1(void *arg) {
    // modify the shared resource without synchronization
    sharedResource = 5;
    return NULL;
}

int *thread2(void *arg) {
    // modify the shared resource without synchronization
    sharedResource = 1;
    
    // You expect for this function to return 1 since you set sharedResourced to 1,
    // but it's possible that the function could return 5. If this thread set the
    // sharedResource to 1, then got interrupted by thread 1 where sharedResource
    // was set to 5, then thread 2 executed again, 5 could be returned which is not
    // what the function intended to do.
    
    return sharedResource;
}

int main(int argc, char *argv[]) {
    
    // Create two threads
    pthread_t p1, p2;
    pthread_create(&p1, &attr, thread1, NULL);
    pthread_create(&p2, &attr, thread2, NULL);
    
    // join waits for the threads to finish
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    
    return 0;
}


