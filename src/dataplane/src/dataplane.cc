
#include <dataplane.hh>



/*
Use vectors to represent the header fields. Global variable that is a pointer to the current header vector. 
Header vector gets updated, and pointer updated to point to header vector whenever change happens. 
*/


/* Temp function to figure out mapping of fields */
int dummyStart() {

    /* Testing values */
    std::string tempHeader[] = {"IP Src", "IP Dest", "Port Src", "Port Dest", "Protocol"};
    int tempHeaderMetadata[] = {32, 32, 16, 16, 8};

    std::string tempMetadata[] = {"Ingress Port", "Egress Port"};
    std::string tempActions[] = {"Drop", "Forward", "NoAction"};

    int tempLengthHeader = tempHeader->length();
    int tempLengthPerm = tempMetadata->length();

    /* Populate initial field values */
    for (int i = 0; i < tempLengthHeader; i++) {
        header.push_back(tempHeader[i]);
        headerMetadata.push_back(tempHeaderMetadata[i]);
    }
    /* Populate perm values */
    for (int i = 0; i < tempLengthPerm; i++) {
        metadata.push_back(tempMetadata[i]);
        actions.push_back(tempActions[i]);
    }

    /* Initial pipeline  */
    simplePipeline = new struct pipeline;

    
    /* Testing values */
    std::string tempExactFields[3][3];
    tempExactFields[0][0] = "IP Src";
    tempExactFields[0][1] = "IP Dest";
    tempExactFields[1][0] = "Port Src";
    tempExactFields[1][1] = "Port Dest";
    tempExactFields[2][0] = "IP Src";
    tempExactFields[2][1] = "Protocol";



    /* Initialize the 3 tables */
    for (int i = 0; i < 3; i++) {
        struct table * temp = new struct table;
        simplePipeline->tableVect.push_back(temp);
        //fprintf(stderr, "SUCESS\n");
        simplePipeline->tableVect[i]->exactFields.push_back(tempExactFields[i][0]);
        simplePipeline->tableVect[i]->exactFields.push_back(tempExactFields[i][1]);
    }

    /* Test if exactfields are valid fields */
    int check = 0;
    for (int i = 0; i < simplePipeline->tableVect.size(); i++) {
        for (int x = 0; x < simplePipeline->tableVect[i]->exactFields.size(); x++) {
            for (int y = 0; y < tempLengthHeader; y++) {
                if (tempHeader[y].compare(simplePipeline->tableVect[i]->exactFields[x]) == 0) {
                    check = 1;
                    break;
                }
            }
            if (check == 0) {
                fprintf(stderr, "Invalid field found asl\n");
            }
            check = 0;
        }
    }

    //fprintf(stderr, "Finished Test\n");

    return 1;


}

// Thread runs this and blocks on data coming in from control plane. Runs correct operation based on data.
int dispatcherDataplane() {
    while(true) {
        if (doneDataplane == 0) {
            pthread_mutex_lock(&readFromControlplane); //Wake up when there is something to be read
            //Determine What to run based on data in readFromControlPlane

            /* Read from the buffer */
            fprintf(stdout, "%s", readControlplaneBuffer);

            //population();
            pthread_mutex_unlock(&readFromControlplane); 
            doneDataplane = 1; //Indicate done
            usleep(1);
        }
    }
    return 1;
}

// Helper function to write data to controlplane
int writeDataToControlplane(char * data, int size) {
    memcpy(writeControlplaneBuffer, data, size);
    pthread_mutex_unlock(&writeToControlplane); //Unlock done when it needs data to be processed
    while(doneWriteDataplane == 0);
    pthread_mutex_lock(&writeToControlplane);
    doneWriteDataplane = 0; //Continue execution once switchboard finishes processing controlplane

    return 1;
}

//Thread runs this and blocks on data coming in from p4
int readDataFromP4() {
    while (true) {
        if (doneReadp4Dataplane == 0) {
            pthread_mutex_lock(&readFromSimplep4); //Wake up when there is something to be read
            //Determine What to run based on data in readFromControlPlane

            /* Read from the buffer */
            fprintf(stdout, "%s", readP4Buffer);

            //population();
            pthread_mutex_unlock(&readFromSimplep4); 
            doneReadp4Dataplane = 1; //Indicate done
            usleep(1);
        }

    }
    return 1;
}

/*
Used to update dataplane configuration based on specified changes in simplep4 program
Check for valid data done in compiler
Return: 1 on sucess and population of respective fields
*/
int population() {
    std::cout << "POPULATION\n";
    return 1;
}


//Initialize dataplane
int dataplaneInit() {
    /* Mutexes */
    pthread_mutex_lock(&writeToControlplane);
    doneWriteDataplane = 0;


    pthread_t threads[NUMTHREADSDP];
#if NUMTHREADSDP == 1
    pthread_create(&threads[0], NULL, (void * (*)(void *))dispatcherDataplane, (void *)1);
#endif
#if NUMTHREADSDP == 2
    pthread_create(&threads[0], NULL, (void * (*)(void *))dispatcherDataplane, (void *)1);
    pthread_create(&threads[1], NULL, (void * (*)(void *))readDataFromP4, (void *)1);
#endif
    return 1;
}

//Function for testing implementation
int dataplaneTest() {
    writeDataToControlplane(testString2, BUFFERSIZE);

    return 1;
}

/*
 Set up initial config and poll in startup state until simpleP4 program compiled 
Return: 1 once done polling
*/
int startUp() {
    //dummyStart();
    //population();
    dataplaneInit();
    return 1;
}
int dataplaneMain() {
    std::cout << "DATAPLANE\n";
    startUp();
    dataplaneTest();
    return 0;
}