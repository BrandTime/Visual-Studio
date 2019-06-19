/****************************************************/
/* File: util.h                                     */
/* Utility functions for the TINY compiler          */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_
#include"GLOBALS.H"
/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2
#if 0
//auxiliary class for union (unnecessary)
class Attribute {
	void copyUnion(const Attribute&);
public:
	enum { TOKEN, INT, STRING }attr;
	union {
		TokenType op;
		int val;
		string name;
	};

	Attribute() :attr(INT),val(0) {};
	Attribute(const string&);
	Attribute(int);
	Attribute(TokenType);
	Attribute(const Attribute& a);
	~Attribute();
	Attribute& operator=(const Attribute&);
	Attribute& operator=(TokenType);
	Attribute& operator= (int);
	Attribute& operator=(const string&);
	void print(ostream& o);
};
#endif
const int MAXCHILDREN = 3;

struct Token {
	string tokenString;
	TokenType token;
	size_t lineno;

	Token(string, TokenType, size_t);
	Token();
	Token(const Token&);
};

struct TreeNode {
	struct shared_ptr<TreeNode> child[MAXCHILDREN];
	struct shared_ptr<TreeNode> sibling;
	NodeKind nodekind;
	union {
		StmtKind stmt;
		ExpKind exp;
	} kind;
	Token attri;
	ExpType type; /* for type checking of exps */
	enum Scope {
		GLOBAL,LOCAL
	}scope;
};


//print the content of a file, currently only support fstream
void printFile(fstream&);
/* Procedure printToken prints a token
 * and its lexeme to the listing file
 */
void printToken(const Token&, ostream&);

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
shared_ptr<TreeNode> newStmtNode(StmtKind);

/* Function newExpNode creates a new expression
 * node for syntax tree construction
 */
shared_ptr<TreeNode>  newNode(ExpKind);

/* Function newExpNode creates a new variable
 * node for syntax tree construction
 */
shared_ptr<TreeNode>  newTreeNode(NodeKind,Token);
 /* procedure printTree prints a syntax tree to the
  * listing file using indentation to indicate subtrees
  */
void printTree(shared_ptr<TreeNode>, ostream&);
/* printSpaces indents by printing spaces */
void printSpaces(ostream& out);
#endif
