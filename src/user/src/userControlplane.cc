#include <control.hh>
#include <user.hh>
/* Everything is up to user implemenation. Contorlmain() is the only thing called by controlplane */

//Function for testing implementation
int testUsercontrol() {
    control.writeFuncMap["Write"](testString3, BUFFERSIZE);
    return 1;
}

//Miss function that user registered
int missFunc() {
    #if SWITCHTEST
        std::cout << "MISSS\n";
    #endif
    testUsercontrol();

    return 1;
}


//Used to register functions
int regFunctions() {
    control.funcMap["Miss"] = missFunc;

    return 1;
}

//Main function that user needs to have an specify functions to register
int controlMain() {
    regFunctions();
    #if SWITCHTEST
        std::cout << "User controlplane TEST\n";
    #endif

    return 1;
}