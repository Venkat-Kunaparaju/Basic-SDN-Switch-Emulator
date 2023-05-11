#include <basic.hh>

#define NUMTHREAD 3
#define MUTEX 1

extern int startUp();
extern int dataplaneMain(); //Dataplane main
extern int controlplaneMain(); //Controlplane main

extern pthread_mutex_t writtenToDataplane; //Used by controlplane
extern int doneControlplane; //Used by controlplane
extern pthread_mutex_t readFromDataplane; //Used by controlplane
extern int doneReadControlplane; //Used by controlplanne


extern pthread_mutex_t readFromControlplane; //Used by dataplane
extern int doneDataplane; //Used by dataplane
extern pthread_mutex_t writeToControlplane; //Used by dataplane
extern int donewriteDataplane; //Used by dataplane

extern char readControlplaneBuffer[BUFFERSIZE];
extern char writeDataplnaeBuffer[BUFFERSIZE];


/* Switchboard data */
char tempBuffer[4096];


/* Switchboard functions */
int dummyFunc();
int threadinit();
int init();
int testFunc();
int main();
int controlToData();
int dataToControl();
int simplep4ToData();



