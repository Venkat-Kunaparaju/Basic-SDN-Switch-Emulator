
/* Example: How a header should get translated to, map the bits the user specifies into a char array 
of the rounded up to nearest bytes. Name is the same as the user specifies 
For example "x bit<17>" -> 
*/
struct header {
    char source_ip[32];
    char dest_ip[32];
    char source_port[32];
    char dest_port[32];
    char type[4];
};

struct metadata {
    int source_ip;
    int dest_ip;
    int source_port;
    int

};

