#ifndef _TEXTBOOK_ALG_H_
#define _TEXTBOOK_ALG_H_
#include"lk_stack.h"
#include"lk_binary_tree.h"
#include<fstream>
#include<utility>
//���������������ո���Ʊ��ȡ��һ���ַ�
static char GetChar(istream &infile){
	char ch;
	while (infile.peek() != EOF
		&& ((ch = infile.get()) == ' '
			|| ch == '\t'))
		;
	return ch;
}
//�̿�����ʵ�ֵ�����ʽֵ�㷨1
//�㷨������
//	(1)����ջ����׺��ʾת��Ϊ��׺��ʾ���Ӽ���������һ����׺���ʽ���ԡ�=������),
//����ת��Ϊ��׺���ʽ������һ������ļ��У��ԡ�=��������
//	(2)Ӧ�ú�׺��ʾ������ʽ��ֵ�����һ�������ļ�������ĺ�׺���ʽ�������ԡ�=��
//��������ֵ�������ʽ��ֵ����Ļ����ʾ����
//������ݽṹ���㷨�����γ���ƣ������ţ�P45-52
template<class Elem>
class ExpressionValue {
private:
	//�ж�ch�Ƿ�Ϊ�����
	static bool IsOperator(char ch);
	//�������������ȼ�
	static int LeftPri(char op);
	//�ұ�����������ȼ�
	static int RightPri(char op);
	//��opndջ��ȡ������������
	static void Get2Operator(Stack<Elem> &opnd,Elem &a1,Elem &a2);
	//�γ�����ָ��(a1)op(a2)�������opndջ
	static void DoOperator(Stack<Elem> &opnd, const Elem &al,
		char op, const Elem &a2);
	//���Ӽ������������׺���ʽת��Ϊ��׺���ʽ���ٴ����������ļ���
	static void PostfixExpression(ofstream &outfile);
	//�������ļ�infile�������׺���ʽ�������׺���ʽ��ֵ
	static void PostfixExpressionValue(ifstream &infile);
public:
	ExpressionValue() {};
	virtual ~ExpressionValue() {};
	//��Ӽ����������׺���ʽֵ֮
	static void Run();
};
#if 0
//�㷨2 ����㷨̫��ʱ�䣬�����ֱ����ջ������ȫ�Ƕ��һ��
//�ö�������ʾ���ʽ�����м���
//������ݽṹ���㷨�����γ���ƣ������ţ�P109-113
class BinTreeExpressionValue {
protected:
	LkBinTree<pair<char,double>> pLkBinTree;//Ϊ�˴���С����������dataӦΪpair
	string inOrder;
	string postOrder;
	bool IsOperator(char ch);
	int GetPrecede(char ch, int adder);//adder��ʾ���ֵ�'(',����
	double DoOperator(char op,double  first, double second);
	void PostExpression(ofstream& outfile);
	//���Ӽ����ж������׺���ʽת��Ϊ��׺���ʽ���ٴ���postOrder��
	void PostExpressionValue();
	//���������к�׺���ʽ��ֵ
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
	unsigned int adder=0,i=0;//adder��ʶ���ֵġ�����������������
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
//�㷨��ʵ�ֲ���
//�㷨1
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

//�㷨 2


#endif // !_TEXTBOOK_ALG_H_

