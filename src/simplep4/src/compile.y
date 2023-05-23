%{
  #include <../../../include/basic.hh>

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
goals:
  goals goal
  | goal
  ;
goal: 
  HEADER CURLYOPEN parser CURLYCLOSE { //Parse through fields
    #if NEWTEST
      fprintf(stderr, "Valid header \n");
    #endif
  }
  | INGRESS CURLYOPEN gressParser CURLYCLOSE { //Parse through ingress tables
    #if NEWTEST
      fprintf(stderr, "Valid ingress \n");
    #endif
  }
  | EGRESS CURLYOPEN gressParser CURLYCLOSE { //Parse through ingress tables
    #if NEWTEST
      fprintf(stderr, "Valid egress \n");
    #endif
  }
  | COMSTART anythingList COMEND {
    #if NEWTEST
      fprintf(stderr, "Valid comment\n");
    #endif
  }
  | VARIABLE {
    #if NEWTEST
      fprintf(stderr, "Variable found: %s\n", $1);
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
  VARIABLE EQUAL CURLYOPEN tableDataParser CURLYCLOSE
  ;
tableDataParser: //Parse information for one table
  exactParser couldParser actionsParser metaParser
  ;
exactParser: //Parse exact fields
  EXACT EQUAL CURLYOPEN fieldList CURLYCLOSE {
    #if COMPILEDEBUG
      fprintf(stderr, "Exact fields parsed\n");
    #endif
  }
  ;
couldParser: //Parse could fields
  COULD EQUAL CURLYOPEN fieldList CURLYCLOSE
  ;
actionsParser:
  ACTIONS EQUAL CURLYOPEN actionList CURLYCLOSE
  ;
metaParser:
  metaParser meta
  | meta
meta:
  MAXNUMENTRIES EQUAL INT SEMICOLON
  | DEFAULTACTION EQUAL action
  ;
actionList:
  actionList action
  | action
  ;
action:
  DROP SEMICOLON
  | FORWARD SEMICOLON
fieldList:
  fieldList field
  | field
  ;
field:
  VARIABLE SEMICOLON
  ;


%%


void yyerror(const char *s) {
    fprintf(stderr, "ERROR: %s\n", s);
}
