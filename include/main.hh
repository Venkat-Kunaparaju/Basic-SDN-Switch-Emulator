#include <basic.hh>

#define NUMTHREAD 3

extern int startUp();
extern int dataplaneMain(); //Dataplane main
extern int controlplaneMain(); //Controlplane main

extern int writtenToDataplane; //Set by controlplane
extern pthread_mutex_t readFromControlplane; //Used by dataplane

