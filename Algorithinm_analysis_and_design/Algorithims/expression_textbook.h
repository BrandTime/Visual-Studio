#ifndef _TEXTBOOK_ALG_H_
#define _TEXTBOOK_ALG_H_
#include"lk_stack.h"
#include"lk_binary_tree.h"
#include<fstream>
#include<utility>
//从输入流中跳过空格和制表符取出一个字符
static char GetChar(istream &infile){
	char ch;
	while (infile.peek() != EOF
		&& ((ch = infile.get()) == ' '
			|| ch == '\t'))
		;
	return ch;
}
//教科书上实现的求表达式值算法1
//算法描述：
//	(1)利用栈将中缀表示转换为后缀表示，从键盘上输入一个中缀表达式（以‘=’结束),
//将其转换为后缀表达式存入在一个输出文件中（以‘=’结束）
//	(2)应用后缀表示计算表达式的值，求从一个输入文件中输入的后缀表达式（假设以‘=’
//结束）的值，将表达式的值在屏幕上显示出来
//详见数据结构与算法分析课程设计（唐宁九）P45-52
template<class Elem>
class ExpressionValue {
private:
	//判断ch是否为运算符
	static bool IsOperator(char ch);
	//左边运算符的优先级
	static int LeftPri(char op);
	//右边运算符的优先级
	static int RightPri(char op);
	//从opnd栈中取出两个操作数
	static void Get2Operator(Stack<Elem> &opnd,Elem &a1,Elem &a2);
	//形成运算指令(a1)op(a2)，结果进opnd栈
	static void DoOperator(Stack<Elem> &opnd, const Elem &al,
		char op, const Elem &a2);
	//将从键盘中输入的中缀表达式转换为后缀表达式，再存入输入流文件中
	static void PostfixExpression(ofstream &outfile);
	//从输入文件infile中输入后缀表达式，并求后缀表达式的值
	static void PostfixExpressionValue(ifstream &infile);
public:
	ExpressionValue() {};
	virtual ~ExpressionValue() {};
	//求从键盘输入的中缀表达式之值
	static void Run();
};
#if 0
//算法2 这个算法太费时间，相较于直接用栈操作完全是多此一举
//用二叉树表示表达式并进行计算
//详见数据结构与算法分析课程设计（唐宁九）P109-113
class BinTreeExpressionValue {
protected:
	LkBinTree<pair<char,double>> pLkBinTree;//为了处理小数，树结点的data应为pair
	string inOrder;
	string postOrder;
	bool IsOperator(char ch);
	int GetPrecede(char ch, int adder);//adder表示出现的'(',个数
	double DoOperator(char op,double  first, double second);
	void PostExpression(ofstream& outfile);
	//将从键盘中读入的中缀表达式转化为后缀表达式，再存入postOrder中
	void PostExpressionValue();
	//求输入流中后缀表达式的值
	void DisplayHelp(const BinTreeNode<pair<char, double> > *r,
		int level, void(*visit)(const double&));
public:
	BinTreeExpressionValue();
	BinTreeExpressionValue(const BinTreeExpressionValue& copy);
	BinTreeExpressionValue& operator=(
		const BinTreeExpressionValue& copy);
	virtual ~BinTreeExpressionValue();
	void Run();
	void Display(void(*visit)(const double&));
};

void BinTreeExpressionValue::PostExpressionValue(ifstream& infile) {
	string temp;
	getline(infile,temp);
	CreatBinaryTree()

	return;
}
int BinTreeExpressionValue::GetPrecede(char ch, int adder) {
	int precede = 0;
	switch (ch) {
	case '+':
	case '-':
		precede = 1;
		break;
	case '*':
	case '/':
		precede = 2;
		break;
	case '^':
		precede = 3;
		break;
	case '=':
		precede = 0;
	default:
	}
	precede += 3 * adder;
	return precede;
}
void BinTreeExpressionValue::PostExpression(ofstream& outfile) {
	char cha;
	double number=0;
	unsigned int adder=0,i=0;//adder标识出现的‘（’，‘）’个数
	Stack<pair<char,int>> oper;
	oper.Push(make_pair('=',GetPrecede('=',adder)));
	while (cin >> cha) {
		if (IsOperator(cha)) {
			if (cha == '(')
				++adder;
			else if (cha == ')')
				--adder;
			else {
				pair<char,int> temp;
				temp=oper.Top();
				while (GetPrecede(cha, adder) <= temp.second) {
					oper.Pop(temp);
					outfile << temp.first;
				}
				oper.Push(make_pair(cha, GetPrecede(cha, adder)));
			}
		}
		else {
			outfile << cha << " ";
		}
	}

	return;
}
BinTreeExpressionValue& BinTreeExpressionValue::operator=(
	const BinTreeExpressionValue& copy) {
	if (&copy != this) {
		if (pLkBinTree)
			pLkBinTree->~LkBinTree();
		pLkBinTree = new LkBinTree<pair<char, double>>(*copy.pLkBinTree);
	}
	return *this;
}
BinTreeExpressionValue::BinTreeExpressionValue(
	const BinTreeExpressionValue& copy) {
	if (pLkBinTree)
		pLkBinTree->~LkBinTree();
	pLkBinTree = new LkBinTree<pair<char, double>>(*copy.pLkBinTree);
}
BinTreeExpressionValue::~BinTreeExpressionValue() {
	pLkBinTree->~LkBinTree();
}
BinTreeExpressionValue::BinTreeExpressionValue() {
	pLkBinTree = nullptr;
}
void BinTreeExpressionValue::DisplayHelp(const BinTreeNode<pair<char, double>> *r,
	int level,void(*visit)(const double&)) {
	if (r) {
		DisplayHelp(r->rChild,level+1,visit);
		for (int i = 0; i < level; ++i)
			cout << "  ";
		(*visit)((r->data).second);
		DisplayHelp(r->lChild, level + 1, visit);
	}
	return;
}
void BinTreeExpressionValue::Display(void(*visit)(const double&)) {
	if (pLkBinTree)
		DisplayHelp(pLkBinTree->GetRoot(), 0, visit);
	else
		throw runtime_error("the tree doesn't exist");
	return;
}
double BinTreeExpressionValue::DoOperator(char op, double first, double second) {
	switch (op) {
	case '+':
		return first + second;
	case '-':
		return first - second;
	case '*':
		return first * second;
	case '/':
		return first / second;
	case '^':
		return pow(first, second);
	default:
		throw runtime_error("Error");
	}
}
bool BinTreeExpressionValue::IsOperator(char ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
		ch == '^' || ch == '(' || ch == ')';
}
#endif
//算法的实现部分
//算法1
template<class Elem>
void ExpressionValue<Elem>::Run() {
	ofstream outfile("temp.dat");
	PostfixExpression(outfile);
	outfile.close();
	ifstream infile("temp.dat");
	PostfixExpressionValue(infile);
	infile.close();
	remove("temp.dat");
	return;
}
template<class Elem>
void ExpressionValue<Elem>::PostfixExpressionValue(ifstream &infile) {
	Stack<Elem> opnd;
	double operand;
	char ch;
	while (infile >> ch, ch != '=') {
		if (IsOperator(ch)) {
			double a1, a2;
			opnd.Pop(a2);
			opnd.Pop(a1);
			DoOperator(opnd, a1, ch, a2);
		}
		else if (isdigit(ch) || ch == '.') {
			cin.putback(ch);
			infile >> operand;
			opnd.Push(operand);
		}
	}
	cout << opnd.Top() << endl;
	return;
}
template<class Elem>
void ExpressionValue<Elem>::PostfixExpression(ofstream &outfile) {
	Stack<char> optr;
	char ch, optrTop, op;
	Elem opnd;
	optr.Push('=');
	optrTop = optr.Top();
	ch = GetChar(cin);
	while (optrTop != '=' || ch != '=') {
		if (isdigit(ch) || ch == '.') {
			cin.putback(ch);
			cin >> opnd;
			outfile << opnd;
			ch = GetChar(cin);
		}
		else if (!IsOperator(ch))
			throw runtime_error("the expression involve incorrecr operator");
		else {
			if (LeftPri(optrTop) < RightPri(ch)) {
				optr.Push(ch);
				ch = GetChar(cin);
			}
			else if (LeftPri(optrTop) > RightPri(ch)) {
				optr.Pop(op);
				outfile << ch;
			}
			else if (LeftPri(optrTop) == RightPri(ch) && ch == ')') {
				optr.Pop(op);
				ch = GetChar(cin);
			}
		}
		optrTop = optr.Top();
	}
	outfile << '=';
	return;
}
template<class Elem>
void ExpressionValue<Elem>::DoOperator(Stack<Elem> &opnd, const Elem &a1,
	char op, const Elem &a2) {
	switch (op) {
	case'+':
		opnd.Push(a1 + a2);
		break;
	case'-':
		opnd.Push(a1 - a2);
		break;
	case'*':
		opnd.Push(a1*a2);
		break;
	case'/':
		if (a2 == 0)
			throw runtime_error("the dividend cannot be 0");
		opnd.Push(a1 / a2);
		break;
	case'^':
		opnd.Push(pow(a1, a2));
		break;
	}
	return;
}
template<class Elem>
void ExpressionValue<Elem>::Get2Operator(Stack<Elem> &opnd, Elem &al, Elem &a2) {
	if (opnd.Pop(a2) && opnd.Pop(a1))
		return;
	else
		throw runtime_error("the expression is not correct");
}
template<class Elem>
int ExpressionValue<Elem>::RightPri(char op) {
	switch (op) {
	case'=':
		return 0;
	case'(':
		return 8;
	case'*':
	case'/':
		return 4;
	case'^':
		return 6;
	case'+':
	case'-':
		return 2;
	case')':
		return 1;
	default:
		throw runtime_error("Error");
	}
}
template<class Elem>
int ExpressionValue<Elem>::LeftPri(char op) {
	switch (op) {
	case'=':
		return 0;
	case'(':
		return 1;
	case'+':
	case'-':
		return 3;
	case'*':
	case'/':
		return 5;
	case'^':
		return 7;
	case')':
		return 8;
	default:
		throw runtime_error("Error");
	}
}
template<class Elem>
bool ExpressionValue<Elem>::IsOperator(char ch) {
	return ch == '=' || ch == '+' || ch == '-' || 
		ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')';
}

//算法 2


#endif // !_TEXTBOOK_ALG_H_

