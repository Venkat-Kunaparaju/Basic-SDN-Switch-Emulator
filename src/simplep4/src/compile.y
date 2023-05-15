%{
  //#include <compile.h>

  // Declare stuff from Flex that Bison needs to know about:
  extern int yylex();
  extern int yyparse();

  void yyerror(const char *s);
%}

%%
whereList:
    whereList
    ;
%%


void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
}