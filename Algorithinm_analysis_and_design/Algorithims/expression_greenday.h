#ifndef _GREENDAY_ALGORITHIM_H_
#define _GREENDAY_ALGORITHIM_H_
//�Լ�ʵ�ֵ�����ʽֵ���㷨
//ֱ������׺��ʽ���м���
//���Լ���С������λ������
//��Ҫ������Ԥ�����ֱ����map����Ӽ���

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
//�жϵ�ǰָ��ָ����ַ��Ƿ�Ϊ���ֵ�һ���֣�������������
bool Isdigit(const char pc) {
	return isdigit(pc) || pc == '.';
}
//�õ���ǰ������һ����������i=0��ʾ��ǰ��������i=1��ʾ��һ��������
Pair<char, unsigned int>& Getchar(string::iterator& cur, const string::iterator& end,
	unsigned int upgrade, int i = 0)
{
	if (i == 0) {
		if (Isdigit(*cur))
			if (cur + 1 != end)
				return Getpair(*(cur + 1), upgrade);
			else
				return Getpair('=', upgrade);
		else//����ǰǡ��Ϊ������ʱ������������
			return 	Getpair(*cur, upgrade);
	}
	else {
		//��ȡ��һ��������ʱ
		if (Isdigit(*cur)) {//��ǰλ�����֣����ʾ�հ�����ѹջ��
			if (cur + 1 != end)
				return	Getpair(*(cur + 1), upgrade);
			else
				return Getpair('=', 0);
		}
		else {
			//��ǰλ�ǲ����������ʾ�հѲ�����ѹջ��Ҫȡ����һ��������Ҫ�ƹ���һ������
			auto next_char = cur + 1;
			while (next_char != end&&
				Isdigit(*next_char)) //�ƹ���һ������
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
	int power = 0;//Power<0�������С�����ֵĶ�ȡ

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
	unsigned int upgrade = 0;//������¼���ŵĲ���

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
