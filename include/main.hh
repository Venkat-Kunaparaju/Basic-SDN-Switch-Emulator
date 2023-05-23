#include <basic.hh>

#define NUMTHREAD 4
#define NUMTHREADMAIN 3
#define MUTEX 1

extern int startUp();
extern int dataplaneMain(); //Dataplane main
extern int controlplaneMain(); //Controlplane main
extern int controlMain(); //Usercontrolplane main
extern int compileMain(); //Compiler main
extern int parseFile(); //Parsing p4 file

//Yacc parsing
extern int yyparse();

#ifndef YY_TYPEDEF_YY_BUFFER_STATE
#define YY_TYPEDEF_YY_BUFFER_STATE
typedef struct yy_buffer_state *YY_BUFFER_STATE;
#endif

#ifndef YY_BUF_SIZE
#define YY_BUF_SIZE 16384
#endif

extern void yypush_buffer_state(YY_BUFFER_STATE);
extern YY_BUFFER_STATE yy_create_buffer(FILE *, int);
extern void yypop_buffer_state();



extern pthread_mutex_t writtenToDataplane; //Used by controlplane
extern int doneControlplane; //Used by controlplane
extern pthread_mutex_t readFromDataplane; //Used by controlplane
extern int doneReadControlplane; //Used by controlplanne

extern pthread_mutex_t readFromControlplane; //Used by dataplane
extern int doneDataplane; //Used by dataplane
extern pthread_mutex_t writeToControlplane; //Used by dataplane
extern int doneWriteDataplane; //Used by dataplane
extern pthread_mutex_t readFromSimplep4; //Used by dataplane
extern int doneReadp4Dataplane; //Used by dataplane

extern pthread_mutex_t writeToDataplane; //Used by p4
extern int doneWriteP4; //Used by p4

extern char readControlplaneBuffer[BUFFERSIZE]; //Used by dataplane
extern char writeControlplaneBuffer[BUFFERSIZE]; //Used by dataplane
extern char readP4Buffer[BUFFERSIZE]; //Used by dataplane

extern char writeDataplaneBuffer[BUFFERSIZE]; //Used by controlplane
extern char readDataplaneBuffer[BUFFERSIZE]; //Used by controlplane

extern char writeDataplaneP4Buffer[BUFFERSIZE]; //Used by compiler


extern struct ctrl control; //Used for interface between user and control plane

/* Switchboard functions */
int dummyFunc();
int threadinit();
int init();
int testFunc();
int main();
int controlToData();
int dataToControl();
int simplep4ToData();

/* Switchboard variables */
int tableType; //1 if Ingress, 0 if Egress






