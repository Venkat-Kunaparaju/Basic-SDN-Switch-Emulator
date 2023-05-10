#include <controlplane.hh>


//Init for controlplane
int controlInit() {
    pthread_mutex_lock(&writtenToDataplane);
    return 1;
}


//Test function for controlplane
int controlTest() {

    /* Write data to buffer here */
    pthread_mutex_unlock(&writtenToDataplane); //Unlock done when it needs data to be processed

    while(doneControlplane == 0);
    pthread_mutex_lock(&writtenToDataplane);
    doneControlplane = 0; //Continue execution once switchboard finishes processing controlplane

    //Second call

    pthread_mutex_unlock(&writtenToDataplane); //Unlock done when it needs data to be processed

    while(doneControlplane == 0);
    pthread_mutex_lock(&writtenToDataplane);
    doneControlplane = 0; //Continue execution once switchboard finishes processing controlplane

    std::cout << "CONTINUING EXECUTION\n";
    return 1;
}


int controlplaneMain() {
    std::cout << "CONTROL\n";
    controlInit();
    controlTest();
    return 0;
}