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
%token CURLYOPEN CURLYCLOSE OPENARROW CLOSEARROW SEMICOLON EQUAL

%%

//Main parsing
goals:
  goals goal
  | goal
  ;
goal: 
  HEADER CURLYOPEN parser CURLYCLOSE //Parse through fields
  | INGRESS CURLYOPEN gressParser CURLYCLOSE //Parse through ingress tables
  | VARIABLE {
      fprintf(stderr, "Variable found: %s\n", $1);
  }
  | error {
      fprintf(stderr, "ERROR FOUND\n");
  }
  ;

//Header parsing
parser:
  parser headerLine
  | headerLine
  ;
headerLine:
  BIT OPENARROW INT CLOSEARROW VARIABLE SEMICOLON { //Works recursively
    fprintf(stderr, "Valid bit map\n");
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
tableDataParser:
  exactParser couldParser actionsParser metaParser
  ;
exactParser:
  EXACT EQUAL CURLYOPEN fieldList CURLYCLOSE
  ;
couldParser:
  COULD EQUAL CURLYOPEN fieldList CURLYCLOSE
  ;
actionsParser:
  ACTIONS EQUAL CURLYOPEN actionList CURLYCLOSE
  ;
metaParser:
  metaParser meta
  | meta
meta:
  MAXNUMENTRIES EQUAL INT
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
