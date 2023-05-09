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
    for (int i = 0; i < NUMTHREAD; i++) { //Create Threads 
        pthread_create(&threads[i], NULL, (void * (*)(void *))threadFuncs[i], NULL);
    }
    for (int i = 0; i < NUMTHREAD; i++) {
        //pthread_join(threads[i], NULL);
    }
#endif
    return 1;
}


//Set up initial state of switchboard
int init() {
    pthread_mutex_init(&readFromControlplane, NULL); //Communicate when the dataplane should wake up and read
    doneDataplane = 0; //Tells switchboard when dataplane is done

    pthread_mutex_lock(&readFromControlplane); //Initial lock
    writtenToDataplane = 0; //Controlplane sets variable to know when information needs to be written to dataplane
    return 1;
}

int main() {
    fprintf(stderr, "MAIN\n");
    init();
    threadinit();
    pthread_mutex_unlock(&readFromControlplane);
    while(doneDataplane == 0);
    doneDataplane = 1;
    pthread_mutex_lock(&readFromControlplane);
    //while(true);
    return 1;
}