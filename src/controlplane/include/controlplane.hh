#include <../../../include/basic.hh>

#define NUMTHREADSCP 1

pthread_mutex_t writtenToDataplane; //Used to communicate information from control to data
int doneControlplane;

pthread_mutex_t readFromDataplane; //Wake up controlplane if there is data needed to be read from dataplane
int doneReadControlplane;

char writeDataplaneBuffer[BUFFERSIZE]; //Buffer for information to send to dataplane
char readDataplaneBuffer[BUFFERSIZE]; //Buffer to read infromation from the dataplane

char * testString1 = "Hello! This is a test to write to dataplane from the controlplane\n";
char * testString3 = "HI! This is a test from user controlplane to dataplane\n";

char * errorMessageFunction = "Error: Function registering issue!\n";


int controlInit();
int writeDataToDataplane(char * buffer, int size);
int controlTest();
int controlplaneMain();
int dispatcherControlplane();
int initFunctions();
int verifyFunctions();



struct ctrl control;


/* Type
Miss -> 1
*/

//Switchboard converts the bits to c++ datatypes. 
//Controlplane stores the field value and field name as a hash table. Key -> name.
/* 
[Type][Space]
[Field name 1][Space][Field value 1];
[Field name N][Space][Field value N];
*/
