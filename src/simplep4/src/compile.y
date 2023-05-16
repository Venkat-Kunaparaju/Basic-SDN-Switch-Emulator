%{
  #include <../../../include/basic.hh>

  // Declare stuff from Flex that Bison needs to know about:
  extern int yylex();
  extern int yyparse();

  void yyerror(const char *s);
%}

%token TEST

%%
goal:
  TEST {
      printf("HELLO");
  }
  ;
%%


void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
}