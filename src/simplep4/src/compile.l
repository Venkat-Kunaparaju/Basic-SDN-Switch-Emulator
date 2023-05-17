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

"Header" {
  return HEADER;
}

"bit" {
  return BIT;
}

"Ingress" {
  return INGRESS;
}

"Egress" {
  return EGRESS;
}

"tables" {
  return TABLES;
}

"exact" {
  return EXACT;
}

"could" {
  return COULD;
}

"actions" {
  return ACTIONS;
}

"maxNumEntries" {
  return MAXNUMENTRIES;
}

"defaultAcion" {
  return DEFAULTACTION;
}

"{" {
  return CURLYOPEN;
}

"}" {
  return CURLYCLOSE;
}

"<" {
  return OPENARROW;
}

">" {
  return CLOSEARROW;
}

";" {
  return SEMICOLON;
}

"=" {
  return EQUAL;
}

[^ \(\)"\n\t;,]+ { //Everything that a variable can not have in it
  memcpy(yylval.stringVal, yytext, 32);
  return VARIABLE;
}

[0-9]+ { //Matches with a sequence of numbers
  yylval.intVal = atoi(yytext);
  return INT;
}

(.*) { //Matches with anything
  memcpy(yylval.stringVal, yytext, 32);
  return NOMATCH;
}

%%