
/* Example file */

/* How a header should get translated to, map the bits the user specifies into a char array 
of the rounded up to nearest bytes. Name is the same as the user specifies 
For example "x bit<17>" -> "char x[3]"
*/
struct header {
    char source_ip[4];
    char dest_ip[4];
    char source_port[4];
    char dest_port[4];
    char type[1];
};

/* Used to keep track of how many bits each entry actually takes up */
struct headerMetadata {
    int source_ip;
    int dest_ip;
    int source_port;
    int dest_port;
    int type;
};

/* Used to keep track of metadata that user might specify */
struct metadata {
    int ingress_port;
    int egresss_port; 
};

