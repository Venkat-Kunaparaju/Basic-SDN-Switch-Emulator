%{
  //#include <compile.hh>
  #include <iostream>
  #include <y.tab.hh>
  extern int yylex();

%}
%option noyywrap
%%

[TEST] {
  return TEST;
}

%%