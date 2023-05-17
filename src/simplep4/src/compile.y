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

%token <stringVal> NOMATCH
%token TEST CHECK

%%
goals:
  lines
  ;
lines:
  lines line
  | line
  ;
line: 
  TEST {
      std::cerr << "Recieved Test\n";
  }
  | CHECK {
      std::cerr << "Recieved Check\n";
  }
  | NOMATCH {
      fprintf(stderr, "Nomatch string: %s\n", $1);
  }
  ;
%%


void yyerror(const char *s) {
    fprintf(stderr, "ERROR: %s\n", s);
}
