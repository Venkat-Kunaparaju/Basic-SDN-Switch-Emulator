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
%token HEADER BIT
%token CURLYOPEN CURLYCLOSE OPENARROW CLOSEARROW SEMICOLON

%%
goals:
  lines
  ;
lines:
  lines line
  | line
  ;
line: 
  | NOMATCH {
      fprintf(stderr, "Nomatch string found: %s\n", $1);
  }
  ;
%%


void yyerror(const char *s) {
    fprintf(stderr, "ERROR: %s\n", s);
}
