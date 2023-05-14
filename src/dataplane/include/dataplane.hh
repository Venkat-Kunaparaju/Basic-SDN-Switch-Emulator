#include <../../../include/basic.hh>

#define NUMTHREADSDP 2

pthread_mutex_t readFromControlplane; //Mutex lock to wake dataplane up if data needs to be updated
int doneDataplane; //Communicates when dataplane is done populating

pthread_mutex_t writeToControlplane; //Mutex lock to wake up switchboard when data needs to be copied to controlplane
int doneWriteDataplane;

pthread_mutex_t readFromSimplep4; //Mutex lock to wake dataplane up if config needs to be updated
int doneReadp4Dataplane;

char readControlplaneBuffer[BUFFERSIZE]; //Buffer to read info from controlplane
char writeControlplaneBuffer[BUFFERSIZE]; //Buffer to write infrom to controlplane
char readP4Buffer[BUFFERSIZE]; //Buffer to read info from p4


char * testString2 = "Hey! This is a test to write to controlplane from the dataplane\n";

int dummyStart();
int dispatcherDataplane();
int population();
int startUp();
int dataplaneMain();
int dataplaneInit();
int writeDataToControlplane(char * buffer, int size);
int dataplaneTest();
int readDataFromP4();



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
    std::vector<int> valActions; //Parallel with actions; Value associated with each action
    std::string def_action; //Default action if no matching entries

    int maxNumEntries; //Max number of possible entries
    int numEntries; //Number of entries in table currently

    bool inEgress; //True if this is an ingress table, false if this is an egress table

    std::string name; //Name of the table


};

struct pipeline
{
    std::vector<table *> tableVect; //Tables composing pipeline
    int numTables;
};

struct pipeline * simplePipeline;
