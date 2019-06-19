/****************************************************/
/* File: globals.h                                  */
/* Global types and vars for TINY compiler          */
/* must come before other include files             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include<iostream>
#include<string>
#include<cctype>
#include<algorithm>
#include<fstream>
#include<iomanip>
#include<vector>
#include<list>
#include<memory>
using namespace std;


/* MAXRESERVED = the MAX number of reserved words */
#define MAXRESERVED 11

typedef enum 
    /* book-keeping tokens */
   {
	ENDFILE, ERROR , _NULL,
    /* reserved words */
    IF,ELSE,WHILE,INT,VOID,DOUBLE,RETURN,
    /* multicharacter tokens */
    ID,NUM,CHAR,STRING,
    /* special symbols */
	PLUS,MINUS,TIMES,OVER,
	LPAREN,RPAREN,SEMI,LBRACKET,RBRACKET,LBRACE,RBRACE,COMMA,
	GT,GEQ,NEQ,EQ,LT,LEQ,ASSIGN
   } TokenType;

/* lookup table of reserved words */
static struct {
	string str;
	TokenType tok;
} reservedWords[MAXRESERVED]
= {
	{"if",IF},{"else",ELSE},{"while",WHILE},
	{"int",INT},{"double",DOUBLE},{"return",RETURN},
	{"void",VOID}
};

extern fstream source; /* source code text file */
extern fstream code; /* code text file for TM simulator */
extern ostream &listing;//print running information

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

typedef enum { VarK, StmtK, ExpK, FuncK, ParamK } NodeKind;
typedef enum {IfK,WhileK,ReadK,WriteK,ReturnK,CallK} StmtKind;
typedef enum {OpK,ConstK,IdK} ExpKind;

/* ExpType is used for type checking */
typedef enum {Void,Integer,Boolean} ExpType;

/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/

/* EchoSource = TRUE causes the source program to
 * be echoed to the listing file with line numbers
 * during parsing
 */
extern bool EchoSource;

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 */
extern bool TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 */
extern bool TraceParse;

/* TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be retported to the listing file
 */
extern bool TraceAnalyze;

/* TraceCode = TRUE causes comments to be written
 * to the TM code file as code is generated
 */
extern bool TraceCode;

/* Error = TRUE prevents further passes if an error occurs */
extern bool Error;
#endif
