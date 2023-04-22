
/* Example file. Can't be used because we need to dynamically change the dataplane functionality during runtime */

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

/* Specify matching fields in simple p4 */
/*
Fields can be either sepcified as exact, or could match. 
Control plane needs to mention exact fields, and could mention could fields.
*/

/* Protocol for communication between simplep4 and dataplane */
/*
Variables
X = Table<table num>:<exact field names seperated by commas (includes comma after last field name)><space>
<exact field names seperated by commas (includes comma after last field name)><space>
<could field names seperated by commas (includes comma after last field name)><space>
<actions seperated by commas (includes comma after last action)><space><default action><space>
<max number of entries><space>


*ACTUAL PROTOCOL*
SYN<space><header fields speerated by commas (includes comma after last field name)><space>
<header metadata seperated by commas(includes comma after last metadata)><space>
NumTables:<number of tables><space>
<X[i] for i in tables>


*/

