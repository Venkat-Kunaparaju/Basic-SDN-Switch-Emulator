#include <main.hh>

//Make multiple threads, each to handle the different component of the application
//Makes dealing with shared resources muche easier


//Dummy function just for random testing
int dummyFunc() {
#if SWITCHTEST
    std::cout << "NOTHING!\n";
#endif
    return 1;
}


//Returns 1 if buffer is not null, 0 if it is
int verifyBufferNotNull(char * buf) {
    if (buf == NULL || buf == '\0') {
        std::cerr << "NULL or empty buffer detected!\n";
        return 0;
    }
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
#if NUMTHREAD == 4
    //Establish workload for each thread
    threadFuncs[0] = (void *) dataplaneMain;
    threadFuncs[1] = (void *) controlplaneMain;
    threadFuncs[2] = (void *) dummyFunc;
    threadFuncs[3] = (void *) compileMain;
    for (int i = 0; i < NUMTHREAD; i++) { //Create Threads 
        pthread_create(&threads[i], NULL, (void * (*)(void *))threadFuncs[i], NULL);
    }
    for (int i = 0; i < NUMTHREAD; i++) {
        //pthread_join(threads[i], NULL);
    }
#endif

    pthread_t interThreads[NUMTHREADMAIN];
    void * interThreadFuncs[NUMTHREADMAIN];
    interThreadFuncs[0] = (void *) controlToData;
    interThreadFuncs[1] = (void *) dataToControl;
    interThreadFuncs[2] = (void *) simplep4ToData;
    /* data -> control, control -> data, simplep4 -> data. 3 threads in total to handle each function in total*/
#if MUTEX
    for (int i = 0; i < NUMTHREADMAIN; i++) {
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


    /* p4 -> data */
    pthread_mutex_init(&writeToDataplane, NULL); 
    doneWriteP4 = 1;

    pthread_mutex_init(&readFromSimplep4, NULL);
    doneReadp4Dataplane = 0;

    pthread_mutex_lock(&readFromSimplep4);
    

    //Set up usercontrolplane
    //funcMap["Write"] = testTemp;
    controlMain();
    return 1;
}

//Used to transfer data from control to data plane
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
                #if SWITCHTEST
                    std::cout << "COPYING BUFFER DATA TO DATAPLANE\n";
                #endif

                if (!(verifyBufferNotNull(writeDataplaneBuffer))) {
                    exit(1);
                }

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

//Used to transfer data from dataplane to controlplane
int dataToControl() {
    bool dataIsValid = true;
    while (true) { //While loop to wake up switchboard whenever there is data needed to be copied to controlplane from dataplane
        if (doneWriteDataplane == 0) {
            pthread_mutex_lock(&writeToControlplane);
                //fprintf(stderr, "%s\n", writeDataplaneBuffer);

            /* CHeck if data is indeed valid here, if not then write back to dataplane buffer with an error */

            if (dataIsValid) {
                /* DO Dataplane copying to controlplane data HERE */
                #if SWITCHTEST
                    std::cout << "COPYING BUFFER DATA TO CONTROLPLANE\n";
                #endif

                if (!(verifyBufferNotNull(writeControlplaneBuffer))) {
                    exit(1);
                }

                /* Test Copying */
                memcpy(readDataplaneBuffer, writeControlplaneBuffer, BUFFERSIZE);

                pthread_mutex_unlock(&readFromDataplane); //Unlock to let know controlplane that it has to read
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


//Used to transfer data from simplep4 runtime to dataplane
int simplep4ToData() {
    bool dataIsValid = true;
    while (true) { //While loop to wake up switchboard when p4 writes data
        if (doneWriteP4 == 0) {
            pthread_mutex_lock(&writeToDataplane);
                //fprintf(stderr, "%s\n", writeDataplaneBuffer);

            /* CHeck if data is indeed valid here, if not then write back and error */

            if (dataIsValid) {
                /* DO copying HERE */
                #if SWITCHTEST
                    std::cout << "COPYING BUFFER DATA TO DATAPLANE FROM P4\n";
                #endif

                if (!(verifyBufferNotNull(writeDataplaneP4Buffer))) {
                    exit(1);
                }

                /* Test Copying */
                memcpy(readP4Buffer, writeDataplaneP4Buffer, BUFFERSIZE);

                pthread_mutex_unlock(&readFromSimplep4); //Unlock to let know dataplane that it has to read
                while(doneReadp4Dataplane == 0);
                pthread_mutex_lock(&readFromSimplep4);
                doneReadp4Dataplane = 0;                   
            }


            pthread_mutex_unlock(&writeToDataplane);
            doneWriteP4 = 1;
            usleep(1);
        }
        // std::cout << "Done\n";
    }
    return 1;
}


//Function to test implementation
int testFunc() {

    // pthread_mutex_unlock(&readFromControlplane);
    // while(doneDataplane == 0);
    // pthread_mutex_lock(&readFromControlplane);
    // doneDataplane = 0;
    while(true);
    //for (int i = 0; i < 100000000; i++); //Poll for a bit to allow other threads to execute
    return 1;
}

//Parse file
int parseFile(char * fileName) {
    FILE * p4File;
    if ((p4File = fopen(fileName, "r"))) {
        yypush_buffer_state(yy_create_buffer(p4File, YY_BUF_SIZE));
        yyparse();
        yypop_buffer_state();
    }

    fclose(p4File);

    return 1;
}

int main() {
    #if SWITCHTEST
        fprintf(stderr, "MAIN\n");
    #endif
    init();
    threadinit();

    parseFile("test.txt");
    parseFile("test.txt");


    testFunc();
    return 1;
}