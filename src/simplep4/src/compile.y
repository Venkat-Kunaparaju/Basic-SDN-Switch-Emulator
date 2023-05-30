%{
  #include <compiley.hh>

  // Declare stuff from Flex that Bison needs to know about:
  extern int yylex();
  extern int yyparse();

  void yyerror(const char *s);
%}

%union {
    int intVal;
    double doubleVal;
    char stringVal[32];
}

%token <stringVal> NOMATCH VARIABLE
%token <intVal> INT
%token HEADER BIT INGRESS EGRESS TABLES EXACT COULD ACTIONS MAXNUMENTRIES DEFAULTACTION DROP FORWARD
%token CURLYOPEN CURLYCLOSE OPENARROW CLOSEARROW SEMICOLON EQUAL COMSTART COMEND ANYTHING

%%

//Main parsing
main:
  goals { //Make sure data is getting parsed properly
    std::cerr << "\nParsed data:\n" << p4Parsing; 
  }
  ;
goals:
  goals goal
  | goal
  ;
goal: 
  HEADER CURLYOPEN parser CURLYCLOSE { //Parse through fields
    #if NEWTEST
      fprintf(stderr, "Valid header \n");
    #endif
    #if COMPILEDEBUG
      fprintf(stderr, "Header parsed\n");
    #endif

    //Indicate end of header parsing
    p4Parsing.append(" ");

  }
  | INGRESS CURLYOPEN gressParser CURLYCLOSE { //Parse through ingress tables
    #if NEWTEST
      fprintf(stderr, "Valid ingress \n");
    #endif
    #if COMPILEDEBUG
      fprintf(stderr, "Ingress tables parsed\n");
    #endif
    setToIngress();
  }
  | EGRESS CURLYOPEN gressParser CURLYCLOSE { //Parse through ingress tables
    #if NEWTEST
      fprintf(stderr, "Valid egress \n");
    #endif
    #if COMPILEDEBUG
      fprintf(stderr, "Egress tables parsed\n");
    #endif
    setToEgress();
  }
  | COMSTART anythingList COMEND {
    #if NEWTEST
      fprintf(stderr, "Valid comment\n");
    #endif
  }
  ;


//Any test parser
anythingList:
  anythingList ANYTHING
  | ANYTHING
  | anythingList VARIABLE
  | VARIABLE
  | anythingList INT
  | INT
  |
  ;

//Header parsing
parser:
  parser headerLine
  | headerLine
  ;
headerLine:
  BIT OPENARROW INT CLOSEARROW VARIABLE SEMICOLON { //Works recursively
  #if SWITCHTEST
    fprintf(stderr, "Valid bit map\n");
  #endif

  //Add header to string
  p4Parsing.append("[");
  p4Parsing.append($5);
  p4Parsing.append(",");
  p4Parsing.append(std::to_string($3));
  p4Parsing.append("]");
  p4Parsing.append(",");
  }
  ;

//Table parsing
gressParser:
  TABLES EQUAL CURLYOPEN tableParser CURLYCLOSE
  ;
tableParser:
   tableParser table
   | table
   ;
table: 
  VARIABLE EQUAL CURLYOPEN tableDataParser CURLYCLOSE {
    #if COMPILEDEBUG
      fprintf(stderr, "%s table parsed\n", $1);
    #endif

    //Add table to parser
    p4Parsing.append($1);
    p4Parsing.append(" ");
    p4Parsing.append(tableParsing);
    tableParsing.clear();
  }
  ;
tableDataParser: //Parse information for one table
  exactParser couldParser actionsParser metaParser {
    //Indicate end of meta parsing
    tableParsing.append(entryParsing);

    metaParsing.erase(metaParsing.length() - 1); //Erase the comma at end
    metaParsing.append(" ");

    tableParsing.append(metaParsing);
    

    entryParsing.clear();
    metaParsing.clear();
  }
  ;
exactParser: //Parse exact fields
  EXACT EQUAL CURLYOPEN fieldList CURLYCLOSE {
    //Indicate end of exact parsing
    tableParsing.append(" ");
  }
  ;
couldParser: //Parse could fields
  COULD EQUAL CURLYOPEN fieldList CURLYCLOSE {
    //Indicate end of could parsing
    tableParsing.append(" ");
  }
  ;
actionsParser:
  ACTIONS EQUAL CURLYOPEN actionList CURLYCLOSE {
    //Indicate end of action parsing
    tableParsing.append(metaParsing);
    tableParsing.append(" ");

    metaParsing.clear();
  }
  ;
metaParser:
  metaParser meta
  | meta
meta:
  MAXNUMENTRIES EQUAL INT SEMICOLON {
    //Parse maxnumentries 
    entryParsing.append(std::to_string($3));
    entryParsing.append(" ");
  }
  | DEFAULTACTION EQUAL action
  | errorHelper  { //Catch errors and report them
    yyerror("Unknown meta variable!");
    YYABORT;
  }
  ;
actionList:
  actionList action
  | action
  ;
action:
  validAction
  | errorHelper  { //Catch errors and report them
    yyerror("Unknown action!");
    YYABORT;
  }
  ;
fieldList:
  fieldList field
  | field
  ;
field:
  VARIABLE SEMICOLON {
    //Parse each field
    tableParsing.append($1);
    tableParsing.append(",");
  }
  ;
errorHelper:
  INT
  | VARIABLE
  | errorHelper SEMICOLON
validAction:
  DROP SEMICOLON {
    //Parse action
    metaParsing.append("Drop");
    metaParsing.append(",");
  }
  | FORWARD SEMICOLON {
    //Parse action
    metaParsing.append("Forward");
    metaParsing.append(",");

  }
  ;
  


%%


void yyerror(const char *s) {
    fprintf(stderr, "Parsing error: %s\n", s);
    setP4Parsing();
}
