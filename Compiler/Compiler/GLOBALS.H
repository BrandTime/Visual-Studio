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


/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 8

typedef enum 
    /* book-keeping tokens */
   {ENDFILE, ERROR , _NULL,
    /* reserved words */
    IF,THEN,ELSE,END,REPEAT,UNTIL,READ,WRITE,
    /* multicharacter tokens */
    ID,NUM,CHAR,STRING,
    /* special symbols */
    ASSIGN,EQ,LT,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI
   } TokenType;
/* states in scanner DFA */
typedef enum {
	START, INASSIGN, INCOMMENT, INNUM, INID, DONE, SCOMMENT,
	MCOMMENT,INCHAR,INSTRING,_ERROR
}
StateType;
/* lookup table of reserved words */
static struct {
	string str;
	TokenType tok;
} reservedWords[MAXRESERVED]
= {
	{"if",IF},{"then",THEN},{"else",ELSE},{"end",END},
	{"repeat",REPEAT},{"until",UNTIL},{"read",READ},
	{"write",WRITE}
};
extern fstream source; /* source code text file */
extern fstream code; /* code text file for TM simulator */
extern ostream &listing;//print running information

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

typedef enum {StmtK,ExpK} NodeKind;
typedef enum {IfK,RepeatK,AssignK,ReadK,WriteK} StmtKind;
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
