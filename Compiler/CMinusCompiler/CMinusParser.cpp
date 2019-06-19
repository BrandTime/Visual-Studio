/****************************************************/
/* File: parse.c                                    */
/* The CMinusParser implementation for the CMinus compiler  */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/
//#if 0
#include "CMinusParser.h"

Token CMinusParser::curToken;
list<Token>::const_iterator CMinusParser::curTokenPos;

void CMinusParser::syntaxError(const string& message, ostream& out) {
	out << endl << ">>> "
		<< "Syntax error at line " << curToken.lineno << ": " << message << endl;
	Error = true;
}
Token CMinusParser::getToken() {
	if (curTokenPos != tokenBuf.cend()) {
		return *curTokenPos++;
	}
	else
		return Token("ENDOFFILE", ENDFILE, -1);
}
void CMinusParser::match(TokenType expected) {
	if (curToken.token == expected)
		curToken = getToken();
	else {
		syntaxError("unexpected token -> ", cerr);
		printToken(curToken, listing);
		listing << "\t";
	}
}

//declaration → var-declaration | fun-declaration
shared_ptr<TreeNode> CMinusParser::declaration() {
	enum Scope{GLOBAL,LOCAL} scope=GLOBAL;
	shared_ptr<TreeNode> temp(nullptr);
	Token typeToken = curToken;//get declaration type
	curToken = getToken();
	Token idToken = curToken;
	temp = newTreeNode();
}
// declaration-list → declaration { declaration }
shared_ptr<TreeNode> CMinusParser::declaration_list() {
	shared_ptr<TreeNode> m_program = declaration();
	shared_ptr<TreeNode> last = m_program;
	while (curToken.token != ENDFILE) {
		if (curToken.token == INT || 
			curToken.token == VOID ||
			curToken.token == SEMI) {
			shared_ptr<TreeNode> temp = declaration();
			if (temp != nullptr) {
				if (m_program == nullptr) {
					m_program = last = temp;
				}
				else {
					last->sibling = temp;
					last = temp;
				}
			}
		}
		else {
			//syntax error handling, not implemented
		}
		curToken = getToken();
	}
	return m_program;
}
//program → declaration-list
shared_ptr<TreeNode> CMinusParser::program() {
	return declaration_list();
}

/****************************************/
/* the primary function of the CMinusParser   */
/****************************************/
/* Function parse returns the newly
 * constructed syntax tree
 */
 shared_ptr<TreeNode> CMinusParser::parse(void) {
	shared_ptr<TreeNode> t = nullptr;
	curTokenPos = tokenBuf.cbegin();
	curToken = getToken();
	if (curToken.token != _NULL) {
		t = stmt_sequence();
		if (curToken.token != ENDFILE)
			syntaxError("Code ends before file\n", cerr);
	}

	return t;
}
//#endif