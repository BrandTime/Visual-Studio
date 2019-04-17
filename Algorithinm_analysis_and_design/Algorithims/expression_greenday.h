#ifndef _GREENDAY_ALGORITHIM_H_
#define _GREENDAY_ALGORITHIM_H_
//自己实现的求表达式值的算法
//直接用中缀形式进行计算
//可以计算小数，多位整数等
//若要加其他预算符，直接在map中添加即可

#include"lk_stack.h"
#include<map>

static map<char, unsigned int> Precede =
{
	map<char,unsigned int>::value_type('+',1),
	map<char,unsigned int>::value_type('-',1),
	map<char,unsigned int>::value_type('*',2),
	map<char,unsigned int>::value_type('/',2),
	map<char,unsigned int>::value_type('^',3),
	map<char,unsigned int>::value_type('(',4)
};

Pair<char, unsigned int>& Getpair(char oper, unsigned int upgrade) {
	return Make_pair(oper, Precede[oper] + Precede['('] * upgrade);
}
double Compute(double first, double second, const char oper) {
	switch (oper)
	{
	case '+':
		return first + second;
	case '-':
		return first - second;
	case '*':
		return first*second;
	case '/':
		return first / second;
	case '^':
		return pow(first, second);
	default:
		throw runtime_error("wrong expression");
	}
}
int Atoi(const char* pc) {
	return *pc - '0';
}
//判断当前指针指向的字符是否为数字的一部分（包括浮点数）
bool Isdigit(const char pc) {
	return isdigit(pc) || pc == '.';
}
//得到当前或者下一个操作符，i=0表示当前操作符，i=1表示下一个操作符
Pair<char, unsigned int>& Getchar(string::iterator& cur, const string::iterator& end,
	unsigned int upgrade, int i = 0)
{
	if (i == 0) {
		if (Isdigit(*cur))
			if (cur + 1 != end)
				return Getpair(*(cur + 1), upgrade);
			else
				return Getpair('=', upgrade);
		else//当当前恰好为操作符时，遇不到（）
			return 	Getpair(*cur, upgrade);
	}
	else {
		//当取下一个操作符时
		if (Isdigit(*cur)) {//当前位是数字，这表示刚把数字压栈，
			if (cur + 1 != end)
				return	Getpair(*(cur + 1), upgrade);
			else
				return Getpair('=', 0);
		}
		else {
			//当前位是操作符，这表示刚把操作符压栈，要取得下一个操作符要绕过下一个数字
			auto next_char = cur + 1;
			while (next_char != end&&
				Isdigit(*next_char)) //绕过下一个数字
				++next_char;
			if (next_char == end)
				return Getpair('=', 0);
			else {
				if (*next_char == ')') {
					if (next_char + 1 != end)
						return Getpair(*(next_char + 1), upgrade - 1);
					else
						return Getpair('=', 0);
				}
				else
					return Getpair(*next_char, upgrade);
			}
		}
	}
}
void Pushnum(Stack<double>& num, string::iterator& cur, const string::iterator& end) {
	int integer_num = 0;
	double double_num = 0;
	int power = 0;//Power<0代表进入小数部分的读取

	while (cur != end&&
		Isdigit(*cur)) {
		if (*cur == '.')
			power = -1;
		else {
			if (power < 0) {
				double_num += pow(10, power)*Atoi(&*cur);
				--power;
			}
			else
				integer_num = 10 * integer_num + Atoi(&*cur);
		}
		cur += 1;
	}
	--cur;
	num.Push(integer_num + double_num);

	return;
}
void Expression() {
	Pair<char, unsigned int> temp_oper;//used for temprary stroage,no further use(number) 
	double final_num;//used for temprary stroage,no further use(operator) 
	Stack<double> num;
	Stack<Pair<char, unsigned int>> oper;
	string expre;
	unsigned int upgrade = 0;//用来记录括号的层数

	cout << "Please input the expression:" << endl;
	cin >> expre;
	for (auto i = expre.begin(); i != expre.end(); ++i) {
		if (*i == '(') {
			++upgrade;
			continue;
		}
		if (*i == ')') {
			upgrade = (upgrade == 0) ? 0 : (--upgrade);
			continue;
		}
		if (Isdigit(*i))
			Pushnum(num, i, expre.end());
		else
			oper.Push(Getchar(i, expre.end(), upgrade, 0));
		while (num.Getlength() >= 2) {
			Pair<char, unsigned int> cur_oper = oper.Top(), next_oper;
			if (cur_oper.first == '=')
				break;
			if (i + 1 != expre.end()) {
				if (*(i + 1) == '(')
					break;
				if (*(i + 1) == ')') {
					if (i + 2 != expre.end())
						next_oper = Getpair(*(i + 2), upgrade - 1);
					else
						next_oper = Getpair('=', 0);
				}
				else
					next_oper = Getchar(i, expre.end(), upgrade, 1);
			}
			else
				next_oper = Getpair('=', 0);
			if (Isdigit(*i) &&
				cur_oper.second >= next_oper.second) {
				double cur_num, prev_num, result;
				num.Pop(cur_num);
				num.Pop(prev_num);
				result = Compute(prev_num, cur_num, cur_oper.first);
				num.Push(result);
				oper.Pop(temp_oper);
			}
			else
				break;
		}
		//cout << "the operator" << endl;
		//oper.Print();
		//cout << "the number " << endl;
		//num.Print();
		//cout << endl;
	}
	num.Pop(final_num);
	cout << "the final result----" << final_num << endl;

	return;
}
#endif
