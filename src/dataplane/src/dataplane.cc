
#include <main.hh>


/*
Use vectors to represent the header fields. Global variable that is a pointer to the current header vector. 
Header vector gets updated, and pointer updated to point to header vector whenever change happens. 
*/

/*
Used to update dataplane configuration based on specified changes in simplep4 program
Check for valid data done in compiler
Return: 1 on sucess and population of respective fields
*/
int population() {

    return 1;
}
/*
 Set up initial config and poll in startup state until simpleP4 program compiled 
Return: 1 once done polling
*/
int startUp() {
    pipe(p4ToDataplane);
    while(writtenToDataplane == 0); //Poll until writtenToDataplane is 1
    population();
    writtenToDataplane = 0; //Reset value to 0 once done reading
    return 1;
}
int main() {
    std::cout << "DATAPLANE\n";
    return 0;
}