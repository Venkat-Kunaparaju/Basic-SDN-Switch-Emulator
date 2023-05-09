
#include <vector>
#include <../../../include/basic.hh>

#define NUMTHREADSDP 1

pthread_mutex_t readFromControlplane; //Mutex lock to wake dataplane up if data needs to be updated
int doneDataplane; //Communicates when dataplane is done populating



/* Vectors used to validate information */
std::vector<std::string> header; //Collection of Fields of header of packet
std::vector<int> headerMetadata; //Parallel to header vector to contain bits considered in field

/* Vectors shouldn't change across compile requests */
std::vector<std::string> metadata; //Collection of Metadata given to packet during pipeline2
std::vector<std::string> actions; //Collection of Actions potentially to give to packet

struct fields
{
    std::vector<std::string> fields; //Includes both metadata and packet header
    std::vector<char *> value;       //Parallel with fields vector and shows values of field to match with

    int numFields; //Number of fields being considered in this entry
};

struct table
{
    std::vector<std::string> exactFields; //Fields that need to be spcified
    std::vector<std::string> couldFields; //Fields that could be specified

    std::vector<fields * > fieldsVect;   //Fields to match with in an entry; Collection of entries
    std::vector<std::string> actions; //Parallel with fieldsVect; Actions associated with entry.
    std::string def_action; //Default action if no matching entries

    int maxNumEntries;
    int numEntries;
};

struct pipeline
{
    std::vector<table *> tableVect; //Tables composing pipeline
    int numTables;
};

struct pipeline * simplePipeline;
