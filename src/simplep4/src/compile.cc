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

    setP4Parsing();

    return 1;
}

//Function to test implementation
int compileTest() {
    writeToDataplaneFromP4(testString4, BUFFERSIZE);
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

//Sets to initial string for p4 parsing
int setP4Parsing () {

    tableParsing.clear();
    metaParsing.clear();
    entryParsing.clear();

    p4Parsing = "SYN "; //Sets the intial state of p4 parsing string
}

//Main function called by switchboard for compiler
int compileMain() {
    #if SWITCHTEST
        std::cout << "COMPILER\n";
    #endif
    compileInit();

    parseFile("test.txt");


    compileTest();
    return 1;
}