# SimpleP4

User writes program in .simplep4 file format to specify forwarding logic for data plane. It is then compiled using lex and yacc and added to the data plane logic. Explicity translate header information into structs in a header file

Dataplane processes packets through the flow tables, and sends misses to the control program to populate rules. Control program then installs flow entry into dataplane. 

Dataplane takes in input files that is composed of packet header and ingress port, and outputs it to a specific file after classification. 


