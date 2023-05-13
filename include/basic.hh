#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <map>
#include <vector>


#define BUFFERSIZE 4906

/* User and control plane resources */
struct ctrl {
    std::map<std::string, int(*)()> funcMap; //Map user defined functions; Used by user
    std::map<std::string, int(*)(char *, int)> writeFuncMap; //Map write controlplane functions; Used by controlplane
    std::vector<std::string> userFuncs;
    std::vector<std::string> controlFuncs;
};

//Helper functions 
int verifyBufferNotNull(char *);
