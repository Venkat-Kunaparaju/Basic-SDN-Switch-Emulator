%{
  //#include <compile.hh>
  #include <iostream>
  #include <y.tab.hh>
  extern int yylex();

%}
%option noyywrap
%%
[ \t\n] {
  //Ignore space and tabs and newline
}

[Tt][Ee][Ss][Tt] {
  //fprintf(stderr, "The string is: %s\n", yytext);
  return TEST;
}

[Cc][Hh][Ee][Cc][Kk] {
  return CHECK;
}

(.*) {
  memcpy(yylval.stringVal, yytext, 32);
  return NOMATCH;
}

%%