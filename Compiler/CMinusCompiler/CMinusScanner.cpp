/****************************************************/
/* File: scan.c                                     */
/* The CMinusScanner implementation for the CMinus compiler */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "CMinusScanner.h"

int CMinusScanner::linepos = 0;
bool CMinusScanner::EOF_flag = false;
string CMinusScanner::tokenString = "";
string CMinusScanner::lineBuf = "";
vector<pair<string, size_t>> CMinusScanner::codeBuf;
size_t CMinusScanner::lineno = 0;
list<Token> CMinusScanner::tokenBuf;

bool CMinusScanner::preProcess(fstream& f) {
	lineno = 0;
	EOF_flag = false;

	while (getline(f, lineBuf)) {
		lineBuf.push_back('\n');
		codeBuf.push_back(make_pair(lineBuf, lineno));
		if (EchoSource)
			listing << "line" << setw(4) << lineno << ": " << lineBuf;
		lineBuf.clear();
		++lineno;
	}
	if (EchoSource)
		listing << endl;
	return true;
}
char CMinusScanner::getNextChar() {
	if (!(linepos < lineBuf.size())) {
		++lineno;
		if (lineno != codeBuf.size()) {
			lineBuf = codeBuf.at(lineno).first;
			linepos = 0;
			return lineBuf.at(linepos++);
		}
		else {
			EOF_flag = true;
			return EOF;
		}
	}
	else
		return lineBuf.at(linepos++);
}
void  CMinusScanner::ungetNextChar() {
	if (!EOF_flag)
		linepos--;
}
TokenType CMinusScanner::reservedLookup(const string& s) {
	int i;
	for (i = 0; i < MAXRESERVED; i++)
		if (s == reservedWords[i].str)
			return reservedWords[i].tok;
	return ID;
}

/****************************************/
/* the primary function of the CMinusScanner  */
/****************************************/
/* function getToken returns the
 * next token in source file
 */
TokenType CMinusScanner::getToken() {
	/* holds current token to be returned */
	TokenType currentToken = _NULL;
	/* current state - always begins at START */
	StateType state = START;
	/* flag to indicate save to tokenString */
	bool save;
	while (state != DONE) {
		char c = getNextChar();
		save = true;
		switch (state) {
		case START:
			if (isdigit(c))
				state = INNUM;
			else if (isalpha(c)||c=='_')
				state = INID;
			else if (c == '<') {
				save = false;
				state = INLESS;
			}
			else if (c == '>') {
				save = false;
				state = INGREAT;
			}
			else if (c == '=') {
				save = false;
				state = INASSIGN;
			}
			else if (c == '!') {
				save = false;
				state = INNEQ;
			}
			else if ((c == ' ') || (c == '\t') || (c == '\n'))
				save = false;
			else if (c == '/') {
				save = false;
				state = INCOMMENT;
			}
			else if (c == '\'')
				state = INCHAR;
			else if (c == '\"')
				state = INSTRING;
			else {
				state = DONE;
				switch (c) {
				case EOF:
					save = false;
					currentToken = ENDFILE;
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
				case '[':
					currentToken = LBRACKET;
					break;
				case ']':
					currentToken = RBRACKET;
					break;
				case '{':
					currentToken = LBRACE;
					break;
				case '}':
					currentToken = RBRACE;
					break;
				case ',':
					currentToken = COMMA;
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
		case INNEQ:
			save = false;
			if (c == '=') {
				currentToken = NEQ;
				state = DONE;
			}
			else {
				ungetNextChar();
				state = _ERROR;
			}
			break;
		case INASSIGN:
			save = false;
			if (c == '=') {
				currentToken = EQ;
				state = DONE;
			}
			else {
				ungetNextChar();
				currentToken = ASSIGN;
				state = DONE;
			}
			break;
		case INGREAT:
			save = false;
			if (c == '=') {
				currentToken = GEQ;
				state = DONE;
			}
			else {
				ungetNextChar();
				currentToken = GT;
				state = DONE;
			}
			break;
		case INLESS:
			save = false;
			if (c == '=') {
				currentToken = LEQ;
				state = DONE;
			}
			else {
				ungetNextChar();
				currentToken = LT;
				state = DONE;
			}
			break;
		case INSTRING:
			save = true;
			if (c == '\"') {
				currentToken = STRING;
				state = DONE;
			}
			break;
		case INCHAR:
			save = true;
			if (getNextChar() == '\'') {
				ungetNextChar();
				state = INCHAR;
			}
			else if (getNextChar() != '\''&&c == '\'') {
				ungetNextChar();
				currentToken = CHAR;
				state = DONE;
			}
			else
				state = _ERROR;
			break;
		case INCOMMENT:
			save = false;
			if (c == '/')
				state = SCOMMENT;//maybe singleline comment
			else if (c == '*')
				state = MCOMMENT;//maybe multiline comment
			break;
		case SCOMMENT:
			save = false;
			if (c == EOF) {
				state = DONE;
				currentToken = ENDFILE;
			}
			else if (c == '\n') {
				state = DONE;
			}
			break;
		case MCOMMENT:
			save = false;
			if (c == '*') {
				c = getNextChar();
				if (c == '/') {
					state = DONE;
				}
				else {
					ungetNextChar();
				}
			}
			break;
		case INNUM:
			if (!isdigit(c)) {
				if (c != '.') {
					/* backup in the input */
					ungetNextChar();
					save = false;
					state = DONE;
					currentToken = NUM;
				}
			}
			break;
		case INID:
			if (!isalpha(c)) {
				if (!isdigit(c) && c != '_') {
					/* backup in the input */
					ungetNextChar();
					save = false;
					state = DONE;
					currentToken = ID;
				}
			}
			break;
		case DONE:
			break;
		case _ERROR:
			cerr << "Syntax error here!" << endl;
			state = DONE;
			currentToken = ERROR;
			break;
		default:
			/* should never happen */
			cerr << "CMinusScanner Bug: state= " << state << endl;
			state = DONE;
			currentToken = ERROR;
			break;
		}
		if (save)
			tokenString.push_back(c);
		if (state == DONE) {
			if (currentToken == ID)
				currentToken = reservedLookup(tokenString);
		}
	}
	return currentToken;
} /* end getToken */
//main function, get token and tokestring
void CMinusScanner::scan(fstream& f) {
	//codeBuf.reserve(100);
	preProcess(f);
	linepos = 0;
	lineno = 0;
	TokenType token = ENDFILE;
	lineBuf = codeBuf.front().first;
	while ((token = getToken()) != ENDFILE) {
		if (token != _NULL) {
			tokenBuf.push_back(Token(tokenString, token, lineno));
			if (TraceScan) {
				listing << "line" << setw(4) << lineno << ":" << ends;
				printToken(Token(tokenString, token, lineno), listing);
			}
		}
		tokenString.clear();
	}
	if (TraceScan)
		listing << endl;
}
void CMinusScanner::print(ostream& o) {
	for (const auto &i : tokenBuf) {
		printToken(i, o);
	}
}