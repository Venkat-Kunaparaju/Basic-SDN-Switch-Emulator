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
%token HEADER BIT INGRESS EGRESS TABLES EXACT COULD ACTIONS MAXNUMENTRIES DEFAULTACTION
%token CURLYOPEN CURLYCLOSE OPENARROW CLOSEARROW SEMICOLON EQUAL

%%
goals:
  goals goal
  | goal
  ;
goal: 
  HEADER CURLYOPEN parser CURLYCLOSE //Parse through fields
  | VARIABLE {
      fprintf(stderr, "Variable found: %s\n", $1);
  }
  ;
parser:
  | parser line
  | line
  ;
line:
  BIT OPENARROW INT CLOSEARROW VARIABLE SEMICOLON { //Works recursively
    fprintf(stderr, "Valid bit map\n");
  }
  ;
%%


void yyerror(const char *s) {
    fprintf(stderr, "ERROR: %s\n", s);
}
