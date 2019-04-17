/****************************************************/
/* File: scan.c                                     */
/* The scanner implementation for the TINY compiler */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"

int Scanner::linepos = 0;
int Scanner::bufsize = 0;
bool Scanner::EOF_flag = false;

bool Scanner::preProcess(ifstream& f) {
	bufsize = linepos = 0;
	EOF_flag = false;
	if (!f) {
		cerr << "file open fail" << endl;
		return false;
	}
	while (!f.bad()) {
		getline(f, lineBuf);
		bool occured = false;//是否出现过"/*"
		int state = 0;
		string::iterator temp = lineBuf.begin();
		if (!occured) {
			for (string::iterator i; i != lineBuf.end(); ++i) {
				if (!occured)
					state = 0;
				switch (state) {
				case 0:
					if (*i == '/') {
						state = 1;
						temp = i;
					}
					break;
				case 1:
					if (*i == '/')
						state = 2;
					else if (*i == '*') {
						occured = true;
					}
					else
						state = 0;
					break;
				case 2:
					i = lineBuf.insert(i - 2, '@');
					i += 2;
					break;
				default:
					cerr << "compiler error" << endl;
				}
			}
		}
		else {
			for(string::iterator i;)
		}

		codeBuf.push_back(lineBuf);
	}
	lineBuf.clear();
	return true;
}
char Scanner::getNextChar(){ 
	
}


void  Scanner::ungetNextChar() {
	if (!EOF_flag) 
		linepos-- ;
}



TokenType Scanner::reservedLookup (const string& s){ 
	int i;
	for (i=0;i<MAXRESERVED;i++)
		if (s==reservedWords[i].str)
			return reservedWords[i].tok;
	return ID;
}

/****************************************/
/* the primary function of the scanner  */
/****************************************/
/* function getToken returns the 
 * next token in source file
 */
TokenType Scanner::getToken(){  
	/* index for storing into tokenString */
	int tokenStringIndex = 0;
    /* holds current token to be returned */
    TokenType currentToken;
	/* current state - always begins at START */
	StateType state = START;
	/* flag to indicate save to tokenString */
	int save;
	while (state != DONE){ 
	    int c = getNextChar();
		save = true;
		switch (state) { 
			case START:
				if (isdigit(c))
					state = INNUM;
				else if (isalpha(c))
					state = INID;
				else if (c == ':')
					state = INASSIGN;
				else if ((c == ' ') || (c == '\t') || (c == '\n'))
					save = false;
				else if (c == '{'){
					save = false;
					state = INCOMMENT;
				}
				else { 
					state = DONE;
					switch (c){
						case EOF:
							save = false;
							currentToken = ENDFILE;
							break;
						case '=':
							currentToken = EQ;
							break;
						case '<':
							currentToken = LT;
							break;
						case '+':
							currentToken = PLUS;
							break;
						case '-':
							currentToken = MINUS;
							break;
						case '*':
							currentToken = TIMES;
							break;
						case '/':
							currentToken = OVER;
							break;
						case '(':
							currentToken = LPAREN;
							break;
						case ')':
							currentToken = RPAREN;
							break;
						case ';':
							currentToken = SEMI;
							break;
						default:
							currentToken = ERROR;
							break;
					}
				}
				break;
			case INCOMMENT:
				save = false;
				if (c == EOF){ 
					state = DONE;
					currentToken = ENDFILE;
				}
				else if (c == '}') 
					state = START;
				break;
			case INASSIGN:
				state = DONE;
				if (c == '=')
					currentToken = ASSIGN;
				else{
					/* backup in the input */
					ungetNextChar();
					save = false;
					currentToken = ERROR;
				}
				break;
			case INNUM:
				if (!isdigit(c)){ 
					/* backup in the input */
					ungetNextChar();
					save = false;
					state = DONE;
					currentToken = NUM;
				}
				break;
			case INID:
				if (!isalpha(c)){ 
					/* backup in the input */
					ungetNextChar();
					save = false;
					state = DONE;
					currentToken = ID;
				}
				break;
			case DONE:
			default: 
				/* should never happen */
				fprintf(listing,"Scanner Bug: state= %d\n",state);
				state = DONE;
				currentToken = ERROR;
				break;
		}
		if ((save) && (tokenStringIndex <= MAXTOKENLEN))
			tokenString[tokenStringIndex++] = (char) c;
		if (state == DONE){ 
			tokenString[tokenStringIndex] = '\0';
			if (currentToken == ID)
				currentToken = reservedLookup(tokenString);
		}
	}
	if (TraceScan) {
		fprintf(listing,"\t%d: ",lineno);
		printToken(currentToken,tokenString);
	}
	return currentToken;
} /* end getToken */

