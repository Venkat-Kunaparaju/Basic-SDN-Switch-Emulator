#include <../../../include/basic.hh>

//Header file for compiling simplep4 program


pthread_mutex_t writeToDataplane; //Mutex lock to wake up switchboard to copy data from p4 to dataplane
int doneWriteP4;

char writeDataplaneP4Buffer[BUFFERSIZE];

char * testString4 = "Hola! This is a message from p4 to the dataplane!\n";

int tableIngressCounter; //Counter to keep track of number of ingress tables
int tableEgressCounter; //Counter to keep track of number of egress tables
int tableType; //Keep track of type of table

int compileInit();
int compileMain();
int writeToDataplaneFromP4(char * buffer, int size);
int compileTest();
int setP4Parsing();


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

extern std::string p4Parsing; //compile.y; Populates string during runtime with the protocol for table communication
extern std::string tableParsing; //Sub helper parser for tables
extern std::string metaParsing; //Sub helper parser for actions
extern std::string entryParsing; //Sub helper parser for max num entries


//Protocol ids
char * initialParse = "SYN ";

//Protocols


/* Specify matching fields in simple p4 */
/*
Fields can be either sepcified as exact, or could match. 
Control plane needs to mention exact fields, and could mention could fields.
*/

/* Protocol for communication between simplep4 and dataplane */
/*
Variables
X = <Table variable name><space>
<exact field names seperated by commas (includes comma after last field name)><space>
<could field names seperated by commas (includes comma after last field name)><space>
<actions seperated by commas (includes comma after last action)>space>
<max number of entries><space>
<default action><space>

Y = [Header field, Header Metadata]

*ACTUAL PROTOCOL*
SYN<space><Ys speerated by commas (includes comma after last field name)><space>
<X[i] for i in tables>


*/

