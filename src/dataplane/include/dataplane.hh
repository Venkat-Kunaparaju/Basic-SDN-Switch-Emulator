
#include <vector>

int p4ToDataplane[2];   //Pipe to communicate MAT information simplep4 program to dataplane
int writtenToDataplane; //Set to 0 if data is empty, 1 if data exists


/* Vectors used to validate information */
std::vector<std::string> header; //Collection of Fields of header of packet
std::vector<int> headerMetadata; //Parallel to header vector to contain bits considered in field
std::vector<std::string> metadata; //Collection of Metadata given to packet during pipeline2
std::vector<std::string> actions; //Collection of Actions potentially to give to packet

struct fields
{
    std::vector<std::string> fields; //Includes both metadata and packet header
    std::vector<char *> value;       //Parallel with fields vector and shows values of field to match with
    int numFields;
};

struct table
{
    std::vector<fields> fieldsVect;   //Fields to match with in an entry; Collection of entries
    std::vector<std::string> actions; //Parallel with fieldsVect; Actions associated with entry.
    int numEntries;
};

struct pipeline
{
    std::vector<table> tableVect; //Tables composing pipeline
    int numTables;
};
