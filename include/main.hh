#include <basic.hh>

#define NUMTHREAD 3

extern int startUp();
extern int dataplaneMain(); //Dataplane main
extern int controlplaneMain(); //Controlplane main

extern pthread_mutex_t writtenToDataplane; //Used by controlplane
extern int doneControlplane; //Used by controlplane


extern pthread_mutex_t readFromControlplane; //Used by dataplane
extern int doneDataplane; //Used by dataplane



