#include <../../../include/basic.hh>

#define NUMTHREADSCP 1

pthread_mutex_t writtenToDataplane; //Used to communicate information from control to data
int doneControlplane;

pthread_mutex_t readFromDataplane; //Wake up controlplane if there is data needed to be read from dataplane
int doneReadControlplane;

char writeDataplaneBuffer[BUFFERSIZE]; //Buffer for information to send to dataplane
char readDataplaneBuffer[BUFFERSIZE]; //Buffer to read infromation from the dataplane

char * testString1 = "Hello! This is a test to write to dataplane from the controlplane\n";


int controlInit();
int writeDataToDataplane(char *, int);
int controlTest();
int controlplaneMain();
int dispatcherControlplane();
