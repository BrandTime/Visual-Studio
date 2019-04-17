#include"String.h"

ostream &operator<<(ostream& out, const String &str) {
	if (str.CStr())
		out << str.CStr();
	else
		out << "";
	return out;
}
istream &operator>>(istream& in, String &str) {
	DList<char> temp;
	char c;
	while ((in.peek() == ' ') || (in.peek() == '\t')) {
		in.get();
	}
	while ((in.peek()) != EOF &&
		(c = in.get()) != '\n') {
		temp.Append(c);
	}
	String temp1(temp);
	str = temp1;//此处必须这么写，必须先生成一个String临时变量，不能直接写str=temp;
				//因为重载赋值构造函数传入的参数是引用，引用是lvalue，而写str=temp中在调用
				//赋值构造函数之前会先调用String的形参是DList的构造函数生成临时String变量
				//这个变量是rvalue，是无法调用赋值构造函数的，运行时会报错显示对象不存在
	return in;
}
const char* String::CStr()const {
	return (const char*)strVal;
}
DList<char> String::Makelist() {
	if (!m_length)
		throw Error("该串为空,无法转换");
	DList<char> temp;
	for (int i = 0; i < m_length; i++)
		temp.Append(strVal[i]);
	temp.Print();
	return temp;
}
bool String::Insert(int pos, const String& copy) {
	pos = (pos < 0) ? 0 : pos;
	pos = (pos > m_length - 1) ? (m_length - 1) : pos;
	char* temp = new char[m_length + strlen(copy.strVal) + 1];
	char* temp1 = new char[m_length + 1];
	if (pos < m_length - 1)
		strcpy(temp1, strVal + pos + 1);
	else
		memset(temp1, 0, m_length + 1);
	strncpy(temp, strVal, pos + 1);
	temp[pos + 1] = '\0';
	strcat(temp, copy.CStr());
	strcat(temp, temp1);
	//delete[]temp1;
	delete[]strVal;
	strVal = temp;
	return true;
}

bool String::Delete(int front, int len) {
	front = (front < 0) ? 0 : front;
	front = (front >= m_length) ? m_length : front;
	if (len >= m_length - front)
		memset(strVal, 0, m_length);
	else {
		char* temp = new char[m_length - len + 1];
		strncpy(temp, strVal, front);
		temp[front + 1] = '\0';
		strcat(temp, strVal + front + len);
		temp[m_length - len + 1] = '\0';
		delete[]strVal;
		strVal = temp;
	}
	return true;
}
char &String::operator[](int i) {
	return strVal[i];
}
String& String::operator=(const String& copy) {
	if ((&copy) != this) {
		delete[]strVal;
		m_length = copy.length();
		strVal = new char[m_length + 1];
		strcpy(strVal, copy.CStr());
		strVal[m_length] = '\0';
		//cout << strVal << endl;
	}
	return *this;
}
//String& String::operator=(DList<char> &copy) {
//	String *cop = new String(copy);
//	m_length = copy.GetLength();
//	delete[]strVal;
//	strVal = cop->strVal;
//	return *this;
//}
int String::length()const {
	return m_length;
}
bool String::empty()const {
	return m_length == 0;
}
String::String() {
	strVal = NULL;
	m_length = 0;
}
String::~String() {
	m_length = 0;
	delete[]strVal;
	strVal = NULL;
}
String::String(const String &copy) {
	m_length = copy.length();
	if (m_length) {
		if (strVal)
			delete[]strVal;
		strVal = new char[m_length + 1];
		strcpy(strVal, copy.CStr());
		strVal[m_length] = '\0';
	}
	else
		strVal = NULL;
}
String::String(const char*copy) {
	if (copy) {
		m_length = strlen(copy);
		strVal = new char[m_length + 1];
		strcpy(strVal, copy);
		strVal[m_length] = '\0';
	}
	else
		String();
}
String::String(DList<char>&copy) {
	m_length = copy.GetLength();
	if (m_length) {
		delete[]strVal;
		strVal = new char[m_length + 1];
		for (int i = 0; i < m_length; i++) {
			char j;
			copy.SetPos(i);
			copy.GetValue(j);
			strVal[i] = j;
		}
		strVal[m_length] = '\0';
	}
	else
		strVal = NULL;
}
String& operator+(String& first, String &second) {
	//该加法操作将第二个参数加到第一个参数后面
	String *result = new String(first);
	if (second.length())
		Concat(*result, second);
	return *result;
}

int FrontReatIndex(String&T, String &P, int pos) {
	if (P.empty() || T.empty())
		return -1;
	int startpos = pos;
	while (startpos <= T.length() - P.length() + 1) {
		int front = 0, rear = P.length() - 1;
		while (front <= rear) {
			if (T[startpos + front] != P[front])
				break;
			if (T[startpos + rear] != P[rear])
				break;
			front++;
			rear--;
		}
		if (front > rear)
			return startpos;
		startpos++;
	}
	return -1;
}
int user_Index(const String &target, const String &original, int pos) {
	if (target.empty() || original.empty())
		return -1;
	const char *cTarget = target.CStr();
	const char *cOrigina = original.CStr();
	const char *ptr = strstr(cTarget + pos, cOrigina);
	if (ptr == NULL)
		return -1;
	else
		return ptr - cTarget;
}
bool Concat(String &addto, String &addon) {
	if (addon.length()) {
		const char *addTo = addto.CStr();
		const char *addOn = addon.CStr();
		char *temp = new char[strlen(addOn) + strlen(addTo) + 1];
		strcpy(temp, addTo);
		strcat(temp, addOn);
		addto = temp;
		delete[]temp;
		return true;
	}
	return false;
}
String Substring(const String &s, int pos, int len) {
	//pos starts from 0,copy len chars from the beginning of pos in s
	if (!s.length())
		return "";
	if (pos >= 0 && len >= 0 && pos < s.length()) {
		len = (len >= s.length() - pos) ? (s.length() - pos) : len;
		const char *str = s.CStr();
		char *temp = new char[len + 1];
		strncpy(temp, str + pos, len);
		temp[len] = '\0';
		String r_str(temp);
		delete[]temp;
		return r_str;
	}
	else {
		String r_str("");
		return r_str;
	}
}
bool Copy(String &copy, String &original) {
	if (original.length()) {
		const char *ori = original.CStr();
		char* temp = new char[strlen(ori) + 1];
		strcpy(temp, ori);
		copy = temp;
		delete[]temp;
		return true;
	}
	return false;
}
bool Copy(String &copy, String & original, int n) {
	if (original.length()) {
		const char *ori = original.CStr();
		char *cop = new char[strlen(ori) - n + 1];
		strcpy(cop, ori + n);
		copy = cop;
		delete[]cop;
		return true;
	}
	return false;
}
bool operator>=(const String &first, const String &second) {
	return strcmp(first.CStr(), second.CStr()) >= 0;
}
bool operator<=(const String &first, const String &second) {
	return strcmp(first.CStr(), second.CStr()) <= 0;
}
bool operator>(const String &first, const String &second) {
	return strcmp(first.CStr(), second.CStr()) > 0;
}
bool operator<(const String &first, const String &second) {
	return strcmp(first.CStr(), second.CStr()) < 0;
}
bool operator!=(const String &first, const String &second) {
	return strcmp(first.CStr(), second.CStr()) != 0;
}
bool operator==(const String &first, const String &second) {
	return strcmp(first.CStr(), second.CStr()) == 0;
}


#if 0
//测试代码
//规定：所有的序号操作都采取和数组相同的方式，所有的序号都从0开始
#include"header.h"

int main(void) {
	//#if 0
	char *temp = "not wrong";
	String str(temp);
	String str_1(str), str_2 = Substring(str, 4, 4);
	int i, j;
	cout << str_1 << endl;
	cout << str_2 << endl;
	DList<char>	list = str.Makelist();
	list.Print();
	//str.Delete(1, 8);

	for (i = 0; i < str.length(); i++)
		cout << "the " << i << " char:  "
		<< str[i] << endl;
	cout << "make a DList:" << endl;
	String strlist;
	cin >> strlist;
	cout << "output of strlist" << endl;
	cout << strlist << endl;
	cout << "The result of the paterrn match between str and str_2" << endl;
	cout << FrontReatIndex(str, str_2, 2) << endl;

	Copy(str_2, str);
	Copy(str_1, str, 2);
	cout << str_1 << endl << str_2 << endl;
	Concat(str, strlist);
	cout << str << endl;
	str = strlist + str_2;
	cout << str << endl;
	//#endif
	system("PAUSE");
	return 0;
}

#endif