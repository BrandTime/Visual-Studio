/****************************************************/
/* File: scan.h                                     */
/* The scanner interface for the TINY compiler      */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _SCAN_H_
#define _SCAN_H_
#include"GLOBALS.H"
/* MAXTOKENLEN is the maximum size of a token */
#define MAXTOKENLEN 40

/* lookup table of reserved words */
static struct{
	string str;
	TokenType tok;
} reservedWords[MAXRESERVED]
= { 
	{"if",IF},{"then",THEN},{"else",ELSE},{"end",END},
	{"repeat",REPEAT},{"until",UNTIL},{"read",READ},
	{"write",WRITE} 
};

/* states in scanner DFA */
typedef enum{
	START, INASSIGN, INCOMMENT, INNUM, INID, DONE
}
StateType;

/* lexeme of identifier or reserved word */
//string tokenString;

/* BUFLEN = length of the input buffer for
   source code lines */
#define BUFLEN 256

class Scanner {
private:
	/* tokenString array stores the lexeme of each token */
	static string tokenString;
	static string lineBuf; /* holds the current line */
	static int linepos; /* current position in LineBuf */
	static int bufsize; /* current size of buffer string */
	static bool EOF_flag; /* corrects ungetNextChar behavior on EOF */
	static vector<string> codeBuf;//holds entire source file
	static vector<string> output;
public:
	/* function getToken returns the
	* next token in source file
	*/
	static TokenType getToken();
	/* getNextChar fetches the next non-blank character
    from lineBuf, reading in a new line if lineBuf is
    exhausted */
	static char getNextChar();
	/* ungetNextChar backtracks one character
    in lineBuf */
	static void ungetNextChar();
	/* lookup an identifier to see if it is a reserved word */
	/* uses linear search */
	static TokenType reservedLookup(const string& s);
	static bool preProcess(ifstream& i);
};


#endif
