/****************************************************/
/* File: scan.h                                     */
/* The scanner interface for the TINY compiler      */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _SCAN_H_
#define _SCAN_H_
#include"GLOBALS.H"
#include"UTIL.H"

class CMinusScanner {
private:
	/* tokenString array stores the lexeme of each token */
	static string tokenString;
	static string lineBuf; /* holds the current line */
	static int linepos; /* current position in LineBuf */
	static size_t lineno;//current line number
	static bool EOF_flag; /* corrects ungetNextChar behavior on EOF */

	/* getNextChar fetches the next non-blank character
	from lineBuf, reading in a new line if lineBuf is
	exhausted */
	static char getNextChar();
	/* lookup an identifier to see if it is a reserved word */
	/* uses linear search */
	static TokenType reservedLookup(const string& s);
	/* function getToken returns the
	* next token in source file
	*/
	static TokenType getToken();
	/* ungetNextChar backtracks one character
	in lineBuf */
	static void ungetNextChar();
	static bool preProcess(fstream& i);
protected://can be used for further compile
	static vector<pair<string,size_t>> codeBuf;//holds entire source file
	static list<Token> tokenBuf;
public:
	static void scan(fstream& i);
	static void print(ostream& o);
};

#endif
