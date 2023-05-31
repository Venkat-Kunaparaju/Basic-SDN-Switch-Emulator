#include <../../../include/basic.hh>

//Header file for lex/yacc

extern int setP4Parsing();
extern int writeToDataplaneFromP4(char *, int);

std::string p4Parsing; //Populates string during runtime with the protocol for table communication
std::string tableParsing; //Sub helper parser for tables
std::string metaParsing; //Sub helper parser for actions
std::string entryParsing; //Sub helper parser for max num entries