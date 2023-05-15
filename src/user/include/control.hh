/* 
Header file to specify resources that the controlplane and user controlplane should have knowledge of 
User controlplane has to include this header file and link the two files together when compiling
*/
int controlMain(); //Main function called by switchboard

extern struct ctrl control;
//extern std::map<std::string, int(*)()> userFuncMap; 
//extern std::map<std::string, int(*)(char *, int)> writeFuncMap;

