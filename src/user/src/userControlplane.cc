#include <control.hh>
/* Everything is up to user implemenation. Contorlmain() is the only thing called by controlplane */

//Function for testing implementation
int testUsercontrol() {
    writeFuncMap["Write"](testString3, BUFFERSIZE);
    return 1;
}

int missFunc() {
    std::cout << "MISSS\n";
    testUsercontrol();

    return 1;
}


//Used to register functions
int regFunctions() {
    userFuncMap["Miss"] = missFunc;

    return 1;
}

//Main function that user has to specifiy 
int controlMain() {
    regFunctions();

    std::cout << "User controlplane TEST\n";

    return 1;
}