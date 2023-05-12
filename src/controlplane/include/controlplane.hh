#include <../../../include/basic.hh>


pthread_mutex_t writtenToDataplane; //Used to communicate information from control to data
int doneControlplane;

pthread_mutex_t readFromDataplane; //Wake up controlplane if there is data needed to be read from dataplane
int doneReadControlplane;

char writeDataplaneBuffer[BUFFERSIZE]; //Buffer for information to send to dataplane

char * testString1 = "Hello! This is a test to write to dataplane from the controlplane\n";
