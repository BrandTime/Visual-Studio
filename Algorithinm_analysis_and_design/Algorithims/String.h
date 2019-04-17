#ifndef _HEADER_H_
#define _HEADER_H_
#include<iostream>
#include<cstring>
#include"D:\OneDrive\program files\Circular Linked List.cpp"

class String {
protected:
	mutable char *strVal;
	int m_length;
public:
	String();
	virtual ~String();
	String(const String &copy);
	String(const char*copy);
	String(DList<char>&copy);
	int length() const;
	bool empty() const;

	bool Delete(int front, int len);//ɾ����front��ʼ����Ϊlen���Ӵ�
	bool Insert(int pos, const String& copy);//��POS��ʼ�����Ӵ�copy
	DList<char> Makelist();//���ַ�����Ϊ���������ɾ��
						   //String& operator=(const String& copy);
	String& operator=(const String &copy);
	//String& operator=(DList<char> &copy);
	char &operator[](int i);
	friend istream& operator>>(istream& in, String &str);
	friend ostream& operator<<(ostream&out, const String &str);
	friend String& operator+(String& first, String &second);
	const char*CStr()const;
};

class Editor {
	//�򵥵��ı��༭����
private:
	//ÿ���ı�Ϊһ�ַ�����ÿ�д�����һ��˫������Ľڵ��У���������
	DList<String> m_buffer;
	int curline;//�е���Ŵ�1��ʼ�������û�
	char m_command;
	ifstream infile;//�����ⲿ����Ĵ�
	ofstream outfile;//��������ɾ�����к͵�ǰ��

	bool Nextline();
	bool Prevline();
	bool Flush();
	bool Readfile();//�ý�����������ˢ�»�����������
	bool Writefile();
	bool Delete();
	bool Insert(String &copy);
	int Search(String &ori);
	bool Changstr(String& target, String& pattern);//�����target���ڵ�ǰ���в��ҵ��Ӵ������Ӵ���pattern�����滻
public:
	Editor(char inFile[], char outFile[]);
	virtual ~Editor() = default;
	bool GetCommand();
	void RunCommand();
};
bool Editor::Readfile() {
	bool proceed = true;
	if (!m_buffer.Empty()) {
		cout << "�ı�����ǿ�; �����ļ�ʱ��������." << endl;
		cout << " �ش�yes��ִ�д˲���? " << endl;
		if (proceed = UserSaysYes())
			m_buffer.Clear();
	}
	curline = 1;

}
bool Editor::Changstr(String& target, String& pattern) {
	if (curline > 0 && curline <= m_buffer.GetLength()) {
		String temp;
		m_buffer.GetValue(temp);
		int pos = user_Index(temp, target);
		if (pos == -1)
			return false;
		String head = Substring(temp, 0, pos + 1),
			tail = Substring(temp, pos + target.length(), temp.length() - target.length() - pos + 1);
		Concat(head, pattern);
		Concat(head, tail);
		m_buffer.Insert(head);
		m_buffer.Prev();
		m_buffer.Delete(temp);
		return true;
	}
	return false;
}
int Editor::Search(String &ori) {
	int i;
	for (i = 0; i < m_buffer.GetLength(); ++i) {
		String temp;
		m_buffer.GetValue(temp);
		if (user_Index(temp, ori) != -1)
			return i;
	}
	if (i == m_buffer.GetLength())
		return -1;
}
bool Editor::Insert(String &copy) {
	if (curline > 0 && curline <= m_buffer.GetLength()) {
		m_buffer.SetPos(curline - 1);
		if (m_buffer.Insert(copy))
			return true;
	}
	return false;
}
bool Editor::Delete() {
	String temp;
	if (curline > 0 && curline <= m_buffer.GetLength()) {
		m_buffer.SetPos(curline - 1);
		if (m_buffer.Delete(temp))
			return true;
	}
	return false;
}
bool Editor::Flush() {
	m_buffer.Clear();
	return true;
}
bool Editor::Prevline() {
	if (curline <= 1)
		return false;
	else {
		--curline;
		return true;
	}
}
bool Editor::Nextline() {
	if (curline + 1 > m_buffer.GetLength())
		return false;
	else {
		++curline;
		return true;
	}
}
bool Concat(String &addto, String &addon);
bool Copy(String &copy, String &original);
//��ԭʼ���ĵ�N���ַ���ʼ���Ƹ�COPy
bool Copy(String &copy, String &oringinal, int n);
//��β�ַ���ģʽƥ���㷨
int FrontReatIndex(String&T, String &P, int pos = 0);
//��ģʽ���ĵ�POS���ַ���ʼ��Ŀ�괮����ģʽƥ��
int user_Index(const String &target, const String &paterrn, int pos = 0);
//��ԭʼ���ĵ�N���ַ���ʼ��ȡ����ΪLEN���Ӵ�
String Substring(const String &s, int pos, int len);
bool operator==(const String&first, const String &second);
bool operator!=(const String &first, const String &second);
bool operator<(const String &first, const String &second);
bool operator>(const String &first, const String &second);
bool operator<=(const String &first, const String &second);
bool operator>=(const String &first, const String &second);
#endif#pragma once
