/****************************************************/
/* File: parse.c                                    */
/* The TinyParser implementation for the TINY compiler  */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/
//#if 0
#include "TinyParser.h"

Token TinyParser::curToken;
list<Token>::const_iterator TinyParser::curTokenPos;

void TinyParser::syntaxError(const string& message, ostream& out) {
	out << endl << ">>> "
		<< "Syntax error at line " << curToken.lineno << ": " << message << endl;
	Error = true;
}
Token TinyParser::getToken() {
	if (curTokenPos != tokenBuf.cend()) {
		return *curTokenPos++;
	}
	else
		return Token("ENDOFFILE", ENDFILE, -1);
}
void TinyParser::match(TokenType expected) {
	if (curToken.token == expected)
		curToken = getToken();
	else {
		syntaxError("unexpected token -> ", cerr);
		printToken(curToken, listing);
		listing << "\t";
	}
}

shared_ptr<TreeNode> TinyParser::stmt_sequence(void) {
	shared_ptr<TreeNode> t = statement();
	shared_ptr<TreeNode> p = t;
	while ((curToken.token != ENDFILE) && (curToken.token != END) &&
		(curToken.token != ELSE) && (curToken.token != UNTIL)) {
		shared_ptr<TreeNode> q;
		match(SEMI);
		q = statement();
		if (q != nullptr) {
			if (t == nullptr)
				t = p = q;
			else { /* now p cannot be nullptr either */
				p->sibling = q;
				p = q;
			}
		}
	}
	return t;
}

shared_ptr<TreeNode> TinyParser::statement(void) {
	shared_ptr<TreeNode> t = nullptr;
	switch (curToken.token) {
	case IF: t = if_stmt(); break;
	case REPEAT: t = repeat_stmt(); break;
	case ID: t = assign_stmt(); break;
	case READ: t = read_stmt(); break;
	case WRITE: t = write_stmt(); break;
	default:
		syntaxError("unexpected token -> " + curToken.tokenString, listing);
		//printToken(curToken, listing);
		curToken = getToken();
		break;
	} /* end case */
	return t;
}

shared_ptr<TreeNode> TinyParser::if_stmt(void) {
	shared_ptr<TreeNode> t = newStmtNode(IfK);
	match(IF);
	t->attri = curToken;
	if (t != nullptr)
		t->child[0] = exp();
	match(THEN);
	if (t != nullptr)
		t->child[1] = stmt_sequence();
	if (curToken.token == ELSE) {
		match(ELSE);
		if (t != nullptr)
			t->child[2] = stmt_sequence();
	}
	match(END);
	return t;
}

shared_ptr<TreeNode> TinyParser::repeat_stmt(void) {
	shared_ptr<TreeNode>  t = newStmtNode(RepeatK);
	match(REPEAT);
	t->attri = curToken;
	if (t != nullptr)
		t->child[0] = stmt_sequence();
	match(UNTIL);
	if (t != nullptr)
		t->child[1] = exp();
	return t;
}

shared_ptr<TreeNode> TinyParser::assign_stmt(void) {
	shared_ptr<TreeNode> t = newStmtNode(AssignK);
	if ((t != nullptr) && (curToken.token == ID))
		t->attri = curToken;
	match(ID);
	match(ASSIGN);
	if (t != nullptr)
		t->child[0] = exp();
	return t;
}

shared_ptr<TreeNode> TinyParser::read_stmt(void) {
	shared_ptr<TreeNode> t = newStmtNode(ReadK);
	match(READ);
	if ((t != nullptr) && (curToken.token == ID))
		t->attri = curToken;
	match(ID);
	return t;
}

shared_ptr<TreeNode> TinyParser::write_stmt(void) {
	shared_ptr<TreeNode> t = newStmtNode(WriteK);
	match(WRITE);
	t->attri = curToken;
	if (t != nullptr)
		t->child[0] = exp();
	return t;
}

shared_ptr<TreeNode> TinyParser::exp(void) {
	shared_ptr<TreeNode> t = simple_exp();
	if ((curToken.token == LT) || (curToken.token == EQ)) {
		shared_ptr<TreeNode> p = newExpNode(OpK);
		if (p != nullptr) {
			p->child[0] = t;
			p->attri = curToken;
			t = p;
		}
		match(curToken.token);
		if (t != nullptr)
			t->child[1] = simple_exp();
	}
	return t;
}

shared_ptr<TreeNode> TinyParser::simple_exp(void) {
	shared_ptr<TreeNode> t = term();
	while ((curToken.token == PLUS) || (curToken.token == MINUS)) {
		shared_ptr<TreeNode> p = newExpNode(OpK);
		if (p != nullptr) {
			p->child[0] = t;
			p->attri = curToken;
			t = p;
			match(curToken.token);
			t->child[1] = term();
		}
	}
	return t;
}

shared_ptr<TreeNode> TinyParser::term(void) {
	shared_ptr<TreeNode> t = factor();
	while ((curToken.token == TIMES) || (curToken.token == OVER)) {
		shared_ptr<TreeNode> p = newExpNode(OpK);
		if (p != nullptr) {
			p->child[0] = t;
			p->attri = curToken;
			t = p;
			match(curToken.token);
			p->child[1] = factor();
		}
	}
	return t;
}

shared_ptr<TreeNode> TinyParser::factor(void) {
	shared_ptr<TreeNode> t =nullptr;
	switch (curToken.token) {
	case NUM:
		t = newExpNode(ConstK);
		if ((t != nullptr) && (curToken.token == NUM))
			t->attri = curToken;
		match(NUM);
		break;
	case ID:
		t = newExpNode(IdK);
		if ((t != nullptr) && (curToken.token == ID))
			t->attri = curToken;
		match(ID);
		break;
	case LPAREN:
		match(LPAREN);
		t = exp();
		match(RPAREN);
		break;
	default:
		syntaxError("unexpected token -> ", cerr);
		printToken(curToken, cerr);
		curToken = getToken();
		break;
	}
	return t;
}

/****************************************/
/* the primary function of the TinyParser   */
/****************************************/
/* Function parse returns the newly
 * constructed syntax tree
 */
 shared_ptr<TreeNode> TinyParser::parse(void) {
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