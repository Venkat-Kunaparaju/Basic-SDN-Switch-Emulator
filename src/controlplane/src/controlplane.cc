#include <controlplane.hh>


//Init for controlplane
int controlInit() {
    /* Mutexes */
    pthread_mutex_lock(&writtenToDataplane);
    doneControlplane = 0; //Set to 0 after locking, allowing main's initial lock to block

   pthread_t threads[NUMTHREADSCP];
#if NUMTHREADSCP == 1
    pthread_create(&threads[0], NULL, (void * (*)(void *))dispatcherControlplane, (void *)1);
#endif
    return 1;
}

// Function to write data to dataplane
int writeDataToDataplane(char * data, int size) {
    memcpy(writeDataplaneBuffer, data, size); //Copy data
    pthread_mutex_unlock(&writtenToDataplane); //Unlock done when it needs data to be processed
    while(doneControlplane == 0);
    pthread_mutex_lock(&writtenToDataplane);
    doneControlplane = 0; //Continue execution once switchboard finishes processing controlplane

    return 1;
}

// Thread runs this and blocks on data coming in from control plane. Runs correct operation based on data.
int dispatcherControlplane() {
    while (true) {
        if (doneReadControlplane == 0) {
            pthread_mutex_lock(&readFromDataplane);

            /* Read from buffer here */
            fprintf(stdout, "%s", readDataplaneBuffer);

            pthread_mutex_unlock(&readFromDataplane);
            doneReadControlplane = 1;
            usleep(1);
        }
    }
    return 1;
}


//Test function for controlplane
int controlTest() {

    /* Write data to buffer here */
    /* Test data to write to buffer */
    writeDataToDataplane(testString1, BUFFERSIZE);

    std::cout << "CONTINUING EXECUTION\n";
    return 1;
}


int controlplaneMain() {
    std::cout << "CONTROL\n";
    controlInit();
    controlTest();
    return 0;
}