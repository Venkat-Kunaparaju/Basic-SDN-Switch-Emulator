#include <main.hh>

//Make multiple threads, each to handle the different component of the application
//Makes dealing with shared resources muche easier
int main() {
    fprintf(stderr, "CHECK\n");
    startUp();
    return 1;
}