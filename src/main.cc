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
    pthread_mutex_init(&readFromControlplane, NULL); //Communicate when the dataplane should wake up and read from controlplane
    doneDataplane = 0; //Tells switchboard when dataplane is done

    pthread_mutex_init(&writtenToDataplane, NULL); //Communicate when the dataplane should wake up and read from controlplane
    doneControlplane = 0; //Tells switchboard when dataplane is done

    pthread_mutex_lock(&readFromControlplane); //Initial lock
    return 1;
}


//Function to test implementation
int testFunc() {

    //Dataplane reading from controlplane data
    pthread_mutex_unlock(&readFromControlplane);
    while(doneDataplane == 0);
    pthread_mutex_lock(&readFromControlplane);
    doneDataplane = 0;
    pthread_mutex_unlock(&readFromControlplane);
    while(doneDataplane == 0);
    pthread_mutex_lock(&readFromControlplane);
    doneDataplane = 0;

    while (true) { //While loop to wake up switchboard whenever there is data needed to be copied to dataplane
        if (doneControlplane == 0) {
            //Controlplane writing data to dataplane
            pthread_mutex_lock(&writtenToDataplane);
            //Do whatever, copying buffer data etc.
            std::cout << "COPYING BUFFER DATA\n";
            pthread_mutex_unlock(&writtenToDataplane);
            doneControlplane = 1;
            usleep(1);
        }
    }
    for (int i = 0; i < 10000; i++); //Poll for a bit to allow other threads to execute
    return 1;
}

int main() {
    fprintf(stderr, "MAIN\n");
    init();
    threadinit();
    testFunc();
    return 1;
}