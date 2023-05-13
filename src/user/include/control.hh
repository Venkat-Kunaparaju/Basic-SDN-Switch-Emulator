/* 
Header file to specify resources that the controlplane and user controlplane should have knowledge of 
User controlplane has to include this header file and link the two files together when compiling
*/
#include <../../../include/basic.hh>

extern char * testString3;

int controlMain(); //Main function called by switchboard

extern std::map<std::string, int(*)()> userFuncMap; 
extern std::map<std::string, int(*)(char *, int)> writeFuncMap;


/* Functions that can change; Used by and defined by user */
int testUserControl();