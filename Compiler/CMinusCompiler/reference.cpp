#include <fstream>
#include <iostream>
#include <string>
#include <strstream>
using namespace std;
#define BUFLEN 256
#define MAXLEN 256
#define MAXTOKENLEN 40
#define MAXCHILDREN 4
static int lineno;
static int linepos = 0; // 读取的字符在 lineBuf 的位置
static int EOF_FLAG = false;
static int bufsize = 0; //lineBuf 的长度
static char lineBuf[BUFLEN];
FILE *source;
char tokenString[MAXTOKENLEN + 1];
string output; // 输出文件
enum TokenType
{
	ENDFILE,
	ERROR,
	IF,
	ELSE,
	INT,
	RETURN,
	VOID,
	WHILE,
	ID,
	NUM,
	ASSIGN,
	EQ,
	LT,
	PLUS,
	MINUS,
	TIMES,
	OVER,
	LPAREN,
	RPAREN,
	SEMI,
	LBRACKET,
	RBRACKET,
	LBRACE,
	RBRACE,
	COMMA,
	GT,
	GEQ,
	NEQ,
	LEQ
};
enum StateType
{
	START,
	INASSIGN,
	INCOMMENT,
	INNUM,
	INID,
	DONE,
	PRECOMMENT,
	AFTERCOMMENT
};
struct
{
	const char* str;
	TokenType tok;
} ReserverWords[6] = {
	{"if", IF}, {"else", ELSE}, {"int", INT}, 
	{"return", RETURN}, {"void", VOID}, {"while " ,WHILE} 
};
																									 
void UnGetNextChar(){
	if (!EOF_FLAG) 
		linepos--;
}
int GetNextChar()
{
	if (!(linepos < bufsize))
	{
		lineno++;
		if (fgets(lineBuf, BUFLEN - 1, source))
		{
			bufsize = strlen(lineBuf);
			linepos = 0;
			return lineBuf[linepos++];
		}
		else
		{
			EOF_FLAG = true;
			return EOF;
		}
	}
	else
	{
		return lineBuf[linepos++];
	}
}
TokenType ReservedLookUp(char *s)
{
	int i;
	for (i = 0; i < 6; i++)
	{
		if (!strcmp(s, ReserverWords[i].str))
		{
			return ReserverWords[i].tok;
		}
	}
	return ID;
}
TokenType GetToken()
{
	StateType state = START; // 初始状态为 startbool save;
	bool save = true;
	TokenType CurrentToken;
	int tokenStringIndex = 0;
	string assign = "";
	while (state != DONE)
	{
		int c = GetNextChar();
		save = true;
		switch (state)
		{
		case START:
			if (isdigit(c))
			{
				state = INNUM;
			}
			else if (isalpha(c))
			{
				state = INID;
			}
			else if ((c == '<') || (c == '>') || (c == '=') || (c == '!'))
			{
				state = INASSIGN;
				assign += char(c);
			}
			else if ((c == ' ') || (c == '\t') || (c == '\n'))
				save = false;
			else if (c == '/')
			{
				save = false;
				state = PRECOMMENT;
			}
			else
			{
				state = DONE;
				switch (c)
				{
				case EOF:
					save = false;
					CurrentToken = ENDFILE;
					break;
				case '+':
					CurrentToken = PLUS;
					break;
				case '-':
					CurrentToken = MINUS;
					break;
				case '*':
					CurrentToken = TIMES;
					break;
				case '(':
					CurrentToken = LPAREN;
					break;
				case ')':
					CurrentToken = RPAREN;
					break;
				case ';':
					CurrentToken = SEMI;
					break;
				case '[':
					CurrentToken = LBRACKET;
					break;
				case ']':
					CurrentToken = RBRACKET;
					break;
				case '{':
					CurrentToken = LBRACE;
					break;
				case '}':
					CurrentToken = RBRACE;
					break;
				case ',':
					CurrentToken = COMMA;
					break;
				default:
					CurrentToken = ERROR;
					break;
				}
			}
			break;
		case INCOMMENT:
			save = false;
			if (c == EOF)
			{
				state = DONE;
				CurrentToken = ENDFILE;
			}
			else if (c == '*')
				state = AFTERCOMMENT;
			else
			{
				state = INCOMMENT;
			}
			break;
		case INASSIGN:
			if (c == '=')
			{
				CurrentToken = EQ;
				state = DONE;
			}
			else if (assign == "!")
			{
				UnGetNextChar();
				save = false;
				CurrentToken = ERROR;
				state = DONE;
			}
			else if (assign == "=")
			{
				UnGetNextChar();
				save = false;
				CurrentToken = ASSIGN;
				state = DONE;
			}
			else if (assign == "<")
			{
				UnGetNextChar();
				save = false;
				CurrentToken = LT;
				state = DONE;
			}
			else
			{
				UnGetNextChar();
				save = false;
				CurrentToken = GT;
				state = DONE;
			}
			break;
		case INNUM:
			if (!isdigit(c))
			{
				UnGetNextChar();
				save = false;
				state = DONE;
				CurrentToken = NUM;
			}
			break;
		case INID:
			if (!isalpha(c))
			{
				UnGetNextChar();
				save = false;
				state = DONE;
				CurrentToken = ID;
			}
			break;
		case PRECOMMENT:
			if (c == '*')
			{
				state = INCOMMENT;
				save = false;
			}
			else
			{
				UnGetNextChar();
				CurrentToken = OVER;
				state = DONE;
			}
			break;
		case AFTERCOMMENT:
			save = false;
			if (c == '/')
			{
				state = START;
			}
			else if (c == '*')
			{
				state = AFTERCOMMENT;
			}
			else
			{
				state = INCOMMENT;
			}
			break;
		case DONE:
		default:
			state = DONE;
			CurrentToken = ERROR;
			break;
		}
		if ((save) && (tokenStringIndex <= MAXTOKENLEN))
		{
			tokenString[tokenStringIndex++] = (char)c;
		}
		if (state == DONE)
		{
			tokenString[tokenStringIndex] = '\0';
			if (CurrentToken == ID)
			{
				CurrentToken = ReservedLookUp(tokenString);
			}
		}
	}
	return CurrentToken;
}
enum NodeKind // 节点类型
{
	FuncK,
	IntK,
	IdK,
	ParamsK,
	ParamK,
	CompK,
	ConstK,
	CallK,
	ArgsK,
	VoidK,
	Var_DeclK,
	Arry_DeclK,
	Arry_ElemK,
	AssignK /*,WhileK*/,
	OpK,
	Selection_StmtK,
	Iteration_StmtK,
	Return_StmtK
};
struct // 节点类型和字符串关系
{
	string str;
	NodeKind nk;
} nodekind[18] = {
	{"Funck", FuncK}, {"IntK", IntK}, {"IdK", IdK}, {"ParamsK", ParamsK}, 
	{"ParamK", ParamK}, {"CompK", CompK}, {"ConstK", ConstK}, {"CallK", CallK},
	{"ArgsK", ArgsK}, {"VoidK", VoidK}, {"Var_DeclK", Var_DeclK}, 
	{"Arry_DeclK", Arry_DeclK}, {"Arry_ElemK", Arry_ElemK}, {"AssignK", AssignK},
				  /*{"WhileK",WhileK},*/ 
	{"OpK", OpK}, {"Selection_StmtK", Selection_StmtK}, 
	{"Iteration_StmtK " ,Iteration_StmtK},{ " Return_StmtK " ,Return_StmtK}
};
struct // 符号与字符串关系
{
	string str;
	TokenType tk;
}
Ope[11] = {{"=", ASSIGN}, {"==", EQ}, {"<", LT}, {"+", PLUS}, {"-", MINUS}, {"*", TIMES}, {"/", OVER}, {">", GT}, {">=", GEQ}, {"!=", NEQ}, {"<=", LEQ}};
string OpeLookUp(TokenType tk) // 操作符转换为字符串
{
	int i;
	for (i = 0; i < 11; i++)
	{
		if (tk == Ope[i].tk)
		{
			return Ope[i].str;
		}
	}
}
string Change(NodeKind nk) // 节点类型转换为字符串
{
	int i;
	for (i = 0; i < 19; i++)
	{
		if (nk == nodekind[i].nk)
		{
			return nodekind[i].str;
			break;
		}
	}
}
TokenType token;
struct TreeNode
{
	struct TreeNode *child[4];
	struct TreeNode *sibling;
	int lineno;
	NodeKind nodekind;
	union {
		TokenType op;
		int val;
		const char *name;
	} attr;
};
TreeNode *declaration_list(void);
TreeNode *declaration(void);
TreeNode *params(void);
TreeNode *param_list(TreeNode *p);
TreeNode *param(TreeNode *p);
TreeNode *compound_stmt(void);
TreeNode *local_declaration(void);
TreeNode *statement_list(void);
TreeNode *statement(void);
TreeNode *expression_stmt(void);
TreeNode *selection_stmt(void);
TreeNode *iteration_stmt(void);
TreeNode *return_stmt(void);
TreeNode *expression(void);
TreeNode *var(void);
TreeNode *simple_expression(TreeNode *p);
TreeNode *additive_expression(TreeNode *p);
TreeNode *term(TreeNode *p);
TreeNode *factor(TreeNode *p);
TreeNode *call(TreeNode *p);
TreeNode *args(void);
char *copyString(char *s)
{
	int n;
	char *t;
	if (s == NULL)
	{
		return NULL;
	}
	n = strlen(s) + 1;
	t = (char *)malloc(n);
	if (t == NULL)
	{
	}
	else
	{
		strcpy(t, s);
	}
	return t;
}
void match(TokenType expected)
{
	if (token == expected)
		token = GetToken();
	else
	{
		cout << "unexpected token" << endl;
	}
}
TreeNode *newNode(NodeKind kind)
{
	TreeNode *t = (TreeNode *)malloc(sizeof(TreeNode));
	int i;
	if (t == NULL)
	{
		;
	}
	else
	{
		for (i = 0; i < 4; i++)
		{
			t->child[i] = NULL;
		}
		t->sibling = NULL;
		t->nodekind = kind;
		t->lineno = lineno;
		if (kind == OpK || kind == IntK || kind == IdK)
		{
			if (kind == IdK)
				t->attr.name = "";
		}
		if (kind == ConstK)
			 t->attr.val = 0;
	}
	return t;
}
TreeNode *declaration_list(void) //declaration_list->declaration_list declaration| declaration
{
	TreeNode *t = declaration();
	TreeNode *p = t;
	while ((token != INT) && (token != VOID) && (token != ENDFILE))
	{
		token = GetToken();
		if (token == ENDFILE)
			break;
	}
	while (token == INT || token == VOID)
	{
		TreeNode *q;
		q = declaration();
		if (q != NULL)
		{
			if (t == NULL)
			{
				t = p = q;
			}
			else
			{
				p->sibling = q;
				p = q;
			}
		}
	}
	match(ENDFILE);
	return t;
}
TreeNode *declaration(void)
{
	TreeNode *t = NULL;
	TreeNode *p = NULL;
	TreeNode *q = NULL;
	TreeNode *s = NULL;
	TreeNode *a = NULL;
	if (token == INT)
	{
		p = newNode(IntK);
		match(INT);
	}
	else //(token==VOID)
	{
		p = newNode(VoidK);
		match(VOID);
	}
	if (p != NULL && token == ID)
	{
		q = newNode(IdK);
		q->attr.name = copyString(tokenString);
		match(ID);
		if (token == LPAREN)
		{
			t = newNode(FuncK);
			t->child[0] = p; //p 是 t 子节点
			t->child[1] = q;
			match(LPAREN);
			t->child[2] = params();
			match(RPAREN);
			t->child[3] = compound_stmt();
		}
		else if (token == LBRACKET)
		{
			t = newNode(Var_DeclK);
			a = newNode(Arry_DeclK);
			t->child[0] = p; //p 是 t 子节点
			t->child[1] = a;
			match(LBRACKET);
			s = newNode(ConstK);
			s->attr.val = atoi(tokenString);
			match(NUM);
			a->child[0] = q;
			a->child[1] = s;
			match(RBRACKET);
			match(SEMI);
		}
		else if (token == SEMI)
		{
			t = newNode(Var_DeclK);
			t->child[0] = p;
			t->child[1] = q;
			match(SEMI);
		}
		else
		{
			;
		}
	}
	else
	{
		;
	}
	return t;
}
TreeNode *params(void) //params_list | void
{
	TreeNode *t = newNode(ParamsK);
	TreeNode *p = NULL;
	if (token == VOID)
	{
		p = newNode(VoidK);
		match(VOID);
		if (token == RPAREN)
		{
			if (t != NULL)
				t->child[0] = p;
		}
		else // 参数列表为 (void id,[ …… ])
		{
			t->child[0] = param_list(p);
		}
	}
	else //(token==INT)
	{
		t->child[0] = param_list(p);
	}
	return t;
}
TreeNode *param_list(TreeNode *k) //params_list->params_list,param | param
{
	TreeNode *t = param(k);
	TreeNode *p = t;
	k = NULL; // 没有要传给 param 的 VoidK ，所以将 k 设为 NULL
	while (token == COMMA)
	{
		TreeNode *q = NULL;
		match(COMMA);
		q = param(k);
		if (q != NULL)
		{
			if (t == NULL)
			{
				t = p = q;
			}
			else
			{
				p->sibling = q;
				p = q;
			}
		}
	}
	return t;
}
TreeNode *param(TreeNode *k)
{
	TreeNode *t = newNode(ParamK);
	TreeNode *p = NULL;
	TreeNode *q = NULL;
	if (k == NULL && token == VOID)
	{
		p = newNode(VoidK);
		match(VOID);
	}
	else if (k == NULL && token == INT)
	{
		p = newNode(IntK);
		match(INT);
	}
	else if (k != NULL)
	{
		p = k;
	}
	if (p != NULL)
	{
		t->child[0] = p;
		if (token == ID)
		{
			q = newNode(IdK);
			q->attr.name = copyString(tokenString);
			t->child[1] = q;
			match(ID);
		}
		if (token == LBRACKET && (t->child[1] != NULL)) //@@@@@@@@@@@@
		{
			match(LBRACKET);
			t->child[2] = newNode(IdK);
			match(RBRACKET);
		}
		else
		{
			return t;
		}
	}
	else
	{
		;
	}
	return t;
}
TreeNode *compound_stmt(void)
{
	TreeNode *t = newNode(CompK);
	match(LBRACE);
	t->child[0] = local_declaration();
	t->child[1] = statement_list();
	match(RBRACE);
	return t;
}
TreeNode *local_declaration(void)
{
	TreeNode *t = NULL;
	TreeNode *q = NULL;
	TreeNode *p = NULL;
	while (token == INT || token == VOID)
	{
		p = newNode(Var_DeclK);
		if (token == INT)
		{
			TreeNode *q1 = newNode(IntK);
			p->child[0] = q1;
			match(INT);
		}
		else if (token == VOID)
		{
			TreeNode *q1 = newNode(VoidK);
			p->child[0] = q1;
			match(INT);
		}
		if ((p != NULL) && (token == ID))
		{
			TreeNode *q2 = newNode(IdK);
			q2->attr.name = copyString(tokenString);
			p->child[1] = q2;
			match(ID);
			if (token == LBRACKET)
			{
				TreeNode *q3 = newNode(Var_DeclK);
				p->child[3] = q3;
				match(LBRACKET);
				match(RBRACKET);
				match(SEMI);
			}
			else if (token == SEMI)
			{
				match(SEMI);
			}
			else
			{
				match(SEMI);
			}
		}
		if (p != NULL)
		{
			if (t == NULL)
				t = q = p;
			else
			{
				q->sibling = p;
				q = p;
			}
		}
	}
	return t;
}
TreeNode *statement_list(void)
{
	TreeNode *t = statement();
	TreeNode *p = t;
	while (IF == token || LBRACKET == token || ID == token || WHILE == token ||
		   RETURN == token || SEMI == token || LPAREN == token || NUM == token)
	{
		TreeNode *q;
		q = statement();
		if (q != NULL)
		{
			if (t == NULL)
			{
				t = p = q;
			}
			else
			{
				p->sibling = q;
				p = q;
			}
		}
	}
	return t;
}
TreeNode *statement(void)
{
	TreeNode *t = NULL;
	switch (token)
	{
	case IF:
		t = selection_stmt();
		break;
	case WHILE:
		t = iteration_stmt();
		break;
	case RETURN:
		t = return_stmt();
		break;
	case LBRACE:
		t = compound_stmt();
		break;
	case ID:
	case SEMI:
	case LPAREN:
	case NUM:
		t = expression_stmt();
		break;
	default:
		token = GetToken();
		break;
	}
	return t;
}
TreeNode *selection_stmt(void)
{
	TreeNode *t = newNode(Selection_StmtK);
	match(IF);
	match(LPAREN);
	if (t != NULL)
	{
		t->child[0] = expression();
	}
	match(RPAREN);
	t->child[1] = statement();
	if (token == ELSE)
	{
		match(ELSE);
		if (t != NULL)
		{
			t->child[2] = statement();
		}
	}
	return t;
}
TreeNode *iteration_stmt(void)
{
	TreeNode *t = newNode(Iteration_StmtK);
	match(WHILE);
	match(LPAREN);
	if (t != NULL)
	{
		t->child[0] = expression();
	}
	match(RPAREN);
	if (t != NULL)
	{
		t->child[1] = statement();
	}
	return t;
}
TreeNode *return_stmt(void)
{
	TreeNode *t = newNode(Return_StmtK);
	match(RETURN);
	if (token == SEMI)
	{
		match(SEMI);
		return t;
	}
	else
	{
		if (t != NULL)
		{
			t->child[0] = expression();
		}
	}
	match(SEMI);
	return t;
}
TreeNode *expression_stmt(void)
{
	TreeNode *t = NULL;
	if (token == SEMI)
	{
		match(SEMI);
		return t;
	}
	else
	{
		t = expression();
		match(SEMI);
	}
	return t;
}
TreeNode *expression(void)
{
	TreeNode *t = var();
	if (t == NULL) // 不是以 ID 开头，只能是 simple_expression 情况
	{
		t = simple_expression(t);
	}
	else // 以 ID 开头，可能是赋值语句，或 simple_expression 中的 var 和 call 类型的情况
		{
			TreeNode *p = NULL;
			if (token == ASSIGN) // 赋值语句
			{
				p = newNode(AssignK);
				match(ASSIGN);
				p->child[0] = t;
				p->child[1] = expression();
				return p;
			}
			else //simple_expression 中的 var 和 call 类型的情况
			{
				t = simple_expression(t);
			}
		}
	return t;
}
TreeNode *var(void)
{
	TreeNode *t = NULL;
	TreeNode *p = NULL;
	TreeNode *q = NULL;
	if (token == ID)
	{
		p = newNode(IdK);
		p->attr.name = copyString(tokenString);
		match(ID);
		if (token == LBRACKET)
		{
			match(LBRACKET);
			q = expression();
			match(RBRACKET);
			t = newNode(Arry_ElemK);
			t->child[0] = p;
			t->child[1] = q;
		}
		else
		{
			t = p;
		}
	}
	return t;
}
TreeNode *simple_expression(TreeNode *k)
{
	TreeNode *t = additive_expression(k);
	k = NULL;
	if (EQ == token || GT == token || GEQ == token || LT == token || LEQ == token || NEQ == token)
	{
		TreeNode *q = newNode(OpK);
		q->attr.op = token;
		q->child[0] = t;
		t = q;
		match(token);
		t->child[1] = additive_expression(k);
		return t;
	}
	return t;
}
TreeNode *additive_expression(TreeNode *k)
{
	TreeNode *t = term(k);
	k = NULL;
	while ((token == PLUS) || (token == MINUS))
	{
		TreeNode *q = newNode(OpK);
		q->attr.op = token;
		q->child[0] = t;
		match(token);
		q->child[1] = term(k);
		t = q;
	}
	return t;
}
TreeNode *term(TreeNode *k)
{
	TreeNode *t = factor(k);
	k = NULL;
	while ((token == TIMES) || (token == OVER))
	{
		TreeNode *q = newNode(OpK);
		q->attr.op = token;
		q->child[0] = t;
		t = q;
		match(token);
		q->child[1] = factor(k);
	}
	return t;
}
TreeNode *factor(TreeNode *k)
{
	TreeNode *t = NULL;
	if (k != NULL) //k 为上面传下来的已经解析出来的以 ID 开头的 var, 可能为 call 或var
		{
			if (token == LPAREN && k->nodekind != Arry_ElemK) //call
			{
				t = call(k);
			}
			else
			{
				t = k;
			}
		}
	else // 没有从上面传下来的 var
	{
		switch (token)
		{
		case LPAREN:
			match(LPAREN);
			t = expression();
			match(RPAREN);
			break;
		case ID:
			k = var();
			if (LPAREN == token && k->nodekind != Arry_ElemK)
			{
				t = call(k);
			}
			else // 如果是连续计算，进入这一步
			{
				t = k;
			}
			break;
		case NUM:
			t = newNode(ConstK);
			if ((t != NULL) && (token == NUM))
			{
				t->attr.val = atoi(tokenString);
			}
			match(NUM);
			break;
		default:
			token = GetToken();
			break;
		}
	}
	return t;
}
TreeNode *call(TreeNode *k)
{
	TreeNode *t = newNode(CallK);
	if (k != NULL)
		t->child[0] = k;
	match(LPAREN);
	if (token == RPAREN)
	{
		match(RPAREN);
		return t;
	}
	else if (k != NULL)
	{
		t->child[1] = args();
		match(RPAREN);
	}
	return t;
}
TreeNode *args(void)
{
	TreeNode *t = newNode(ArgsK);
	TreeNode *s = NULL;
	TreeNode *p = NULL;
	if (token != RPAREN)
	{
		s = expression();
		p = s;
		while (token == COMMA)
		{
			TreeNode *q;
			match(COMMA);
			q = expression();
			if (q != NULL)
			{
				if (s == NULL)
				{
					s = p = q;
				}
				else
				{
					p->sibling = q;
					p = q;
				}
			}
		}
	}
	if (s != NULL)
	{
		t->child[0] = s;
	}
	return t;
}
int blank_number = 0;
void PreOrder(TreeNode *t)
{
	string blank = " ";
	int i;
	for (i = 0; i < blank_number; i++)
	{
		blank += " ";
	}
	if (t != NULL)
	{
		if (t->nodekind == OpK)
		{
			cout << blank << "Op: " << OpeLookUp(t->attr.op) << endl;
			output += blank + "Op: " + OpeLookUp(t->attr.op) + "\n";
		}
		else if (t->nodekind == IdK)
		{
			cout << blank << Change(t->nodekind) << ": " << t->attr.name << endl;
			output += blank + Change(t->nodekind) + ": " + t->attr.name + "\n";
		}
		else if (t->nodekind == ConstK)
		{
			cout << blank << Change(t->nodekind) << ": " << t->attr.val << endl;
			int n = t->attr.val;
			strstream ss;
			string s;
			ss << n;
			ss >> s;
			output += blank + Change(t->nodekind) + ": " + s + "\n";
		}
		else if (t->nodekind == AssignK)
		{
			cout << blank << "Assign" << endl;
			output += blank + "Assign" + "\n";
		}
		else if (t->nodekind == Selection_StmtK)
		{
			cout << blank << "If" << endl;
			output += blank + "If" + "\n";
		}
		else if (t->nodekind == Iteration_StmtK)
		{
			cout << blank << "While" << endl;
			output += blank + "While" + "\n";
		}
		else if (t->nodekind == Return_StmtK)
		{
			cout << blank << "Return" << endl;
			output += blank + "Return" + "\n";
		}
		else
		{
			cout << blank << Change(t->nodekind) << endl;
			output += blank + Change(t->nodekind) + "\n";
		}
	}
	for (i = 0; i < MAXCHILDREN; i++)
	{
		if (t->child[i] != NULL)
		{
			blank_number += 2;
			PreOrder(t->child[i]);
			blank_number -= 2;
		}
	}
	if (t->sibling != NULL)
	{
		PreOrder(t->sibling);
	}
}
void parse(void)
{
	TreeNode *t;
	cout << "Syntax tree:" << endl;
	token = GetToken();
	t = declaration_list();
	PreOrder(t);
}
void main()
{
	char *file = (char *)malloc(100); // 打开的文件名
	string result;					  // 输出结果文件名
	cout << " 请输入文件名 . 例如： gcd.c-" << endl;
	scanf("%s", file);
	while ((source = fopen(file, "r")) == NULL)
	{
		cout << " 文件名无效 , 请重新输入 " << endl;
		scanf("%s", file);
	}
	ofstream write; // 输出文件
	result = string(file) + "-Result.txt";
	write.open(result);
	write << "Syntax tree:" << endl;
	parse();
	write << output;
	write.close();
	system("PAUSE");
}