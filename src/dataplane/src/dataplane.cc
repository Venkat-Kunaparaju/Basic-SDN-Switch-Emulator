
#include <main.hh>

/*
 Poll in startup state until simpleP4 program compiled 
Return: 1 on success and population of respective fields
*/
int startUp() {
    pipe(p4ToDataplane);
    while(writtenToDataplane == 0); //Poll until writtenToDataplane is 1


    writtenToDataplane = 0; //Reset value to 0 once done reading
    return 1;
}
int main() {
    std::cout << "DATAPLANE\n";
    return 0;
}