/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NOMATCH = 258,
     VARIABLE = 259,
     INT = 260,
     HEADER = 261,
     BIT = 262,
     INGRESS = 263,
     EGRESS = 264,
     TABLES = 265,
     EXACT = 266,
     COULD = 267,
     ACTIONS = 268,
     MAXNUMENTRIES = 269,
     DEFAULTACTION = 270,
     DROP = 271,
     FORWARD = 272,
     CURLYOPEN = 273,
     CURLYCLOSE = 274,
     OPENARROW = 275,
     CLOSEARROW = 276,
     SEMICOLON = 277,
     EQUAL = 278,
     COMSTART = 279,
     COMEND = 280,
     ANYTHING = 281
   };
#endif
/* Tokens.  */
#define NOMATCH 258
#define VARIABLE 259
#define INT 260
#define HEADER 261
#define BIT 262
#define INGRESS 263
#define EGRESS 264
#define TABLES 265
#define EXACT 266
#define COULD 267
#define ACTIONS 268
#define MAXNUMENTRIES 269
#define DEFAULTACTION 270
#define DROP 271
#define FORWARD 272
#define CURLYOPEN 273
#define CURLYCLOSE 274
#define OPENARROW 275
#define CLOSEARROW 276
#define SEMICOLON 277
#define EQUAL 278
#define COMSTART 279
#define COMEND 280
#define ANYTHING 281




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 11 "src/simplep4/src/compile.y"
{
    int intVal;
    double doubleVal;
    char stringVal[32];
}
/* Line 1529 of yacc.c.  */
#line 107 "build/y.tab.hh"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

