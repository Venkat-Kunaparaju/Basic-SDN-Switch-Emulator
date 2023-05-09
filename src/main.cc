#include <main.hh>

//Make multiple threads, each to handle the different component of the application
//Makes dealing with shared resources muche easier

int dummyFunc() {
    std::cout << "NOTHING!\n";

    return 1;
}

//Initialize threads to handle each component
int threadinit() {
    pthread_t threads[NUMTHREAD];
    void * threadFuncs[NUMTHREAD];
#if NUMTHREAD == 3
    //Establish workload for each thread
    threadFuncs[0] = (void *) dataplaneMain;
    threadFuncs[1] = (void *) controlplaneMain;
    threadFuncs[2] = (void *) dummyFunc;
    for (int i = 0; i < NUMTHREAD; i++) //Create Threads
        pthread_create(&threads[i], NULL, (void * (*)(void *))threadFuncs[i], NULL);
    for (int i = 0; i < NUMTHREAD; i++)
        pthread_join(threads[i], NULL);
#endif

    return 1;
}

int main() {
    fprintf(stderr, "CHECK\n");
    threadinit();
    return 1;
}