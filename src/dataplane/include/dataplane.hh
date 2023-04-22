
#include <vector>

int p4ToDataplane[2];   //Pipe to communicate MAT information simplep4 program to dataplane
int writtenToDataplane; //Set to 0 if data is empty, 1 if data exists

std::vector<std::string> header;
std::vector<std::string> metadata;

struct fields
{
    std::vector<std::string> fields; //Includes both metadata and packet header
    std::vector<int> value;          //Parallel with above vector and shows values of field to match with
    int numFields;
};

struct table
{
    std::vector<fields> fieldsVect;   //Fields to match with in an entry; Collection of entries
    std::vector<std::string> actions; //Fields
    int numEntries;
};

struct tables
{
    std::vector<table> tableVect;
    int numTables;
};
