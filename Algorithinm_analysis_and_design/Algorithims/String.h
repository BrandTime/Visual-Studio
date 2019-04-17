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

	bool Delete(int front, int len);//删除从front开始长度为len的子串
	bool Insert(int pos, const String& copy);//从POS开始插入子串copy
	DList<char> Makelist();//将字符串变为链表方便插入删除
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
	//简单的文本编辑器类
private:
	//每行文本为一字符串，每行储存在一个双向链表的节点中，即缓冲区
	DList<String> m_buffer;
	int curline;//行的序号从1开始，面向用户
	char m_command;
	ifstream infile;//缓存外部输入的串
	ofstream outfile;//用来缓存删除的行和当前行

	bool Nextline();
	bool Prevline();
	bool Flush();
	bool Readfile();//用接下来的内容刷新缓冲区的内容
	bool Writefile();
	bool Delete();
	bool Insert(String &copy);
	int Search(String &ori);
	bool Changstr(String& target, String& pattern);//传入的target是在当前行中查找的子串，该子串用pattern串来替换
public:
	Editor(char inFile[], char outFile[]);
	virtual ~Editor() = default;
	bool GetCommand();
	void RunCommand();
};
bool Editor::Readfile() {
	bool proceed = true;
	if (!m_buffer.Empty()) {
		cout << "文本缓存非空; 读入文件时将复盖它." << endl;
		cout << " 回答yes将执行此操作? " << endl;
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
//从原始串的第N个字符开始复制给COPy
bool Copy(String &copy, String &oringinal, int n);
//首尾字符串模式匹配算法
int FrontReatIndex(String&T, String &P, int pos = 0);
//从模式串的第POS个字符开始与目标串进行模式匹配
int user_Index(const String &target, const String &paterrn, int pos = 0);
//从原始串的第N个字符开始截取长度为LEN的子串
String Substring(const String &s, int pos, int len);
bool operator==(const String&first, const String &second);
bool operator!=(const String &first, const String &second);
bool operator<(const String &first, const String &second);
bool operator>(const String &first, const String &second);
bool operator<=(const String &first, const String &second);
bool operator>=(const String &first, const String &second);
#endif#pragma once
