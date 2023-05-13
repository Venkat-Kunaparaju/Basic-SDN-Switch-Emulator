#include <../../../include/basic.hh>

//Header file for compiling simplep4 program




//Protocols


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

