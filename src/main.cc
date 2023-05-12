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

    pthread_t interThreads[NUMTHREAD];
    void * interThreadFuncs[NUMTHREAD];
    interThreadFuncs[0] = (void *) controlToData;
    interThreadFuncs[1] = (void *) dataToControl;
    interThreadFuncs[2] = (void *) simplep4ToData;
    /* data -> control, control -> data, simplep4 -> data. 3 threads in total to handle each function in total*/
#if MUTEX
    for (int i = 0; i < NUMTHREAD; i++) {
        pthread_create(&interThreads[i], NULL, (void * (*)(void *))interThreadFuncs[i], NULL);
    }


#endif
    return 1;
}

//Set up initial state of switchboard
int init() {

    /* control ->data */
    pthread_mutex_init(&readFromControlplane, NULL); //Communicate when the switchboard should wake up and read from controlplane
    doneDataplane = 0; //Tells contrtolplane when switcboard is done

    pthread_mutex_init(&writtenToDataplane, NULL); //Communicate when the dataplane should wake up and read from switchboard
    doneControlplane = 1; //Tells switchboard when dataplane is done; Needs to be initially 1 (race condition)

    pthread_mutex_lock(&readFromControlplane); //Initial lock 


    /* data -> control */
    pthread_mutex_init(&writeToControlplane, NULL); 
    doneWriteDataplane = 1;

    pthread_mutex_init(&readFromDataplane, NULL); 
    doneReadControlplane = 0;
    
    pthread_mutex_lock(&readFromDataplane);
    return 1;
}

int controlToData() {
    bool dataIsValid = true;
    while (true) { //While loop to wake up switchboard whenever there is data needed to be copied to dataplane from contorlplane;
        if (doneControlplane == 0) {
            //Controlplane writing data to dataplane
            pthread_mutex_lock(&writtenToDataplane);
                //fprintf(stderr, "%s\n", writeDataplaneBuffer);

            /* CHeck if data is indeed valid here, if not then write back to controlplane buffer with an error */

            if (dataIsValid) {
                /* DO Dataplane copying from controlplane data HERE */
                std::cout << "COPYING BUFFER DATA TO DATAPLANE\n";

                /* Test Copying */
                memcpy(readControlplaneBuffer, writeDataplaneBuffer, BUFFERSIZE);

                pthread_mutex_unlock(&readFromControlplane); //Unlock to let know dataplane that it has to read
                while(doneDataplane == 0);
                pthread_mutex_lock(&readFromControlplane);
                doneDataplane = 0;                   
            }


            pthread_mutex_unlock(&writtenToDataplane);
            doneControlplane = 1;
            usleep(1);
        }
        // std::cout << "Done\n";
    }
    return 1;
}

int dataToControl() {
    bool dataIsValid = true;
    while (true) { //While loop to wake up switchboard whenever there is data needed to be copied to dataplane from contorlplane;
        if (doneWriteDataplane == 0) {
            //Controlplane writing data to dataplane
            pthread_mutex_lock(&writeToControlplane);
                //fprintf(stderr, "%s\n", writeDataplaneBuffer);

            /* CHeck if data is indeed valid here, if not then write back to controlplane buffer with an error */

            if (dataIsValid) {
                /* DO Dataplane copying from controlplane data HERE */
                std::cout << "COPYING BUFFER DATA TO CONTROLPLANE\n";

                /* Test Copying */
                memcpy(readDataplaneBuffer, writeControlplaneBuffer, BUFFERSIZE);

                pthread_mutex_unlock(&readFromDataplane); //Unlock to let know dataplane that it has to read
                while(doneReadControlplane == 0);
                pthread_mutex_lock(&readFromDataplane);
                doneReadControlplane = 0;                   
            }


            pthread_mutex_unlock(&writeToControlplane);
            doneWriteDataplane = 1;
            usleep(1);
        }
        // std::cout << "Done\n";
    }
    return 1;
}

int simplep4ToData() {

    return 1;
}


//Function to test implementation
int testFunc() {

    // pthread_mutex_unlock(&readFromControlplane);
    // while(doneDataplane == 0);
    // pthread_mutex_lock(&readFromControlplane);
    // doneDataplane = 0;
    while(true);
    for (int i = 0; i < 100000000; i++); //Poll for a bit to allow other threads to execute
    return 1;
}

int main() {
    fprintf(stderr, "MAIN\n");
    init();
    threadinit();
    testFunc();
    return 1;
}