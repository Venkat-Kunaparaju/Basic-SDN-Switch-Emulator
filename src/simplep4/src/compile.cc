#include <compile.hh>


//TODO: Set up comm channels with dataplane

//Function to write to dataplane from compiler
int writeToDataplaneFromP4(char * data, int size) {
    memcpy(writeDataplaneP4Buffer, data, size);
    pthread_mutex_unlock(&writeToDataplane); //Unlock done when it needs data to be processed
    while(doneWriteP4 == 0);
    pthread_mutex_lock(&writeToDataplane);
    doneWriteP4 = 0; //Continue execution once switchboard finishes processing controlplane

    return 1;
}

//Init function for compile
int compileInit() {
    pthread_mutex_lock(&writeToDataplane);
    doneWriteP4 = 0;

    return 1;
}

//Function to test implementation
int compileTest() {
    writeToDataplaneFromP4(testString4, BUFFERSIZE);
    return 1;
}

//Main function called by switchboard for compiler
int compileMain() {
    std::cout << "COMPILER\n";
    compileInit();
    compileTest();
    return 1;
}