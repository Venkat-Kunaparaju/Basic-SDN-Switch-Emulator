#include <../../../include/basic.hh>


pthread_mutex_t writtenToDataplane; //Used to communicate information from control to data
int doneControlplane;

char writeDataplaneBuffer[4096]; //Buffer for information to send to dataplane



