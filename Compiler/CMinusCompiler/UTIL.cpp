/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"

void printFile(fstream& io) {
	if (io) {
		string temp;
		while (getline(io, temp)) {
			 io<< temp << endl;
		}
	}
}
/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken(const Token& toke ,ostream& out){ 
	switch (toke.token) {
	case INT:
	case DOUBLE:
	case VOID:
	case IF:
	case ELSE:
	case WHILE:
	case RETURN:
		out << "reserved word: " << toke.tokenString << endl;
		break;
	case ASSIGN: out << "=" << endl;  break;
	case GT: out << ">" << endl; break;
	case GEQ:out << ">=" << endl; break;
	case LT: out << "<" << endl; break;
	case LEQ:out << "<=" << endl; break;
	case NEQ:out << "!=" << endl; break;
	case EQ: out << "==" << endl; break;
	case LPAREN: out << "(" << endl; break;
	case RPAREN: out << ")" << endl; break;
	case LBRACKET:out << "[" << endl; break;
	case RBRACKET:out << "]" << endl; break;
	case LBRACE:out << "{" << endl; break;
	case RBRACE:out << "}" << endl; break;
	case COMMA:out << "," << endl; break;
	case SEMI: out << ";" << endl; break;
	case PLUS: out << "+" << endl; break;
    case MINUS: out << "-" << endl; break;
    case TIMES: out << "*" << endl; break;
    case OVER:  out << "/" << endl; break;
    case ENDFILE: out << "EOF" << endl; break;
    case NUM:
		out << "NUM, val= " << toke.tokenString << endl;
		break;
    case ID:
		out << "ID, name= " << toke.tokenString << endl;
		break;
    case ERROR:
		out << "ERROR: " << toke.tokenString << endl;
		break;
	case CHAR:
		out << "CHAR: " << toke.tokenString << endl;
		break;
	case STRING:
		out << "STRING: " << toke.tokenString << endl;
		break;
    default: /* should never happen */
		out << "Unknown token: " << toke.tokenString << endl;
  }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
shared_ptr<TreeNode> newStmtNode(StmtKind kind){
	shared_ptr<TreeNode> t=make_shared<TreeNode>();
	int i;
	if (t==nullptr)
		cerr << "Out of memory error here!" << endl;
	else {
		for (i=0;i<MAXCHILDREN;i++) 
			t->child[i] = nullptr;
		t->sibling = nullptr;
		t->nodekind = StmtK;
		t->kind.stmt = kind;
	}
	return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
shared_ptr<TreeNode> newTreeNode(NodeKind kind,Token token){
	shared_ptr<TreeNode> t =make_shared<TreeNode>();
	int i;
	if (t==nullptr)
		cerr << "Out of memory error here!" << endl;
	else {
		for (i=0;i<MAXCHILDREN;i++) 
			t->child[i] = nullptr;
		t->sibling = nullptr;
		t->nodekind = kind;
		t->attri = token;
		t->type = Void;
	}
	return t;
}

shared_ptr<TreeNode>  newVarNode(NodeKind kind) {
	shared_ptr<TreeNode> t = make_shared<TreeNode>();
	int i;
	if (t == nullptr)
		cerr << "Out of memory error here!" << endl;
	else {
		for (i = 0; i < MAXCHILDREN; i++)
			t->child[i] = nullptr;
		t->sibling = nullptr;
		t->nodekind = VarK;
		t->type = Void;
	}
	return t;
}
/* printSpaces indents by printing spaces */
void printSpaces(ostream& out){ 
	int i;
	for (i=0;i<indentno;i++)
	  out << " ";
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
#if 0
void printTree( shared_ptr<TreeNode> tree,ostream& out){ 
	int i;
	INDENT;
	while (tree != nullptr) {
		//out << "line" << setw(4) << tree->attri.lineno << ends;
		printSpaces(out);
		if (tree->nodekind == FuncK) {
			out << "Function declaration: "
				<<
				<< " " << pNode->name << endl;
		}
		else if (tree->nodekind == VarK) {
			out << "Variable declaration: "
				<< scan->key_word[(int)pNode->type].str
				<< " " << pNode->name;
			if (pNode->bArr) out << "[" << pNode->iArrSize << "] ";
			out << endl;
			break;
		}
		else if (tree->nodekind == ParamK) {
			out << "parameter: "
				<< tree->attri.tokenString
				<< " " << pNode->name;
			if (pNode->bArr) out << "[]";
			out << endl;
			break;
		}
		else if (tree->nodekind == StmtK){
			switch (tree->kind.stmt) {
			case IfK:
				out << "If" << endl;
				break;
			case WhileK:
				out<<
			case ReadK:
				out << "Read: " << tree->attri.tokenString << endl;
				break;
			case WriteK:
				out << "Write" << endl;
				break;
			default:
				out << "Unknown ExpNode kind" << endl;
				break;
			}
		}
		else if (tree->nodekind == ExpK){
			switch (tree->kind.exp) {
			case OpK:
				out << "Op:";
				printToken(tree->attri, out);
				break;
			case ConstK:
				out << "Const: " <<atof(tree->attri.tokenString.c_str()) << endl;
				break;
			case IdK:
				out << "Id: " << tree->attri.tokenString << endl;
				break;
			default:
				out << "Unknown ExpNode kind" << endl;
				break;
			}
		}
		else
			out << "Unknown node kind" << endl;
		for (i=0;i<MAXCHILDREN;i++)
			printTree(tree->child[i],out);
		tree = tree->sibling;
	}
	UNINDENT;
}
#endif

#if 0
Attribute::Attribute(int i) {
	val = i;
	attr = INT;
}
Attribute::Attribute(TokenType t) {
	op = t;
	attr = TOKEN;
}
Attribute::Attribute(const string& s) {
	new(&name) string(s);
	attr = STRING;
}
Attribute& Attribute::operator=(const Attribute& copy) {
	if (&copy != this) {
		copyUnion(copy);
		attr = copy.attr;
	}
	return *this;
}
Attribute::Attribute(const Attribute& copy) {
	if (&copy != this) {
		copyUnion(copy);
		attr = copy.attr;
	}
}
Attribute& Attribute::operator=(const string& s) {
	if (attr == STRING) {
		name = s;
	}
	else {
		new(&name) string(s);
		attr = STRING;
	}
	return *this;
}
Attribute& Attribute::operator=(int i) {
	if (attr == STRING) {
		name.~string();
	}
	attr = INT;
	val = i;
	return *this;
}
Attribute::~Attribute() {
	if (attr == STRING) {
		name.~string();
	}
}
Attribute& Attribute::operator=(TokenType t) {
	if (attr == STRING) {
		name.~string();
	}
	attr = TOKEN;
	op = t;
	return *this;
}
void Attribute::copyUnion(const Attribute& copy) {
	if (attr == STRING) {
		name.~string();
	}
	switch (copy.attr) {
	case INT:
		val = copy.val;
		break;
	case TOKEN:
		op = copy.op;
		break;
	case STRING:
		new(&name) string(copy.name);
		break;
	default:
		cerr << "Error happens here!" << endl;
	}
}
void Attribute::print(ostream& o) {
	switch (attr) {
	case TOKEN:
		o << op << endl;
		break;
	case STRING:
		o << name << endl;
		break;
	case INT:
		o << val << endl;
		break;
	default:
		cerr << "ERROR HERE" << endl;
	}
}
#endif

Token::Token(string s, TokenType t, size_t i) :
	tokenString(s),lineno(i), token(t) {};
Token::Token() :tokenString("ERROR"), lineno(-1), token(ERROR) {}
Token::Token(const Token& to) {
	if (&to != this) {
		this->lineno = to.lineno;
		this->token = to.token;
		this->tokenString = to.tokenString;
	}
}