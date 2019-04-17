#pragma once
#include<iostream>
#include<string>
#include<cstdio>
using namespace std;

#define OCCUPIED 1
#define UNOCCUPIED 0
#define MAX_ERROR_MESSAGE_LEN 100

// ͨ���쳣��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
class Error
{
private:
	// ���ݳ�Ա
	string message;// �쳣��Ϣ

public:
	//  ��������
	Error(string mes = "һ�����쳣!")	// ���캯�� 
	{
		message = mes;		// �����쳣��Ϣ
	}
	Error(int i) {
		if (i == 1)
			message = "�ڴ�ռ䲻�㣬�����ڴ�ʧ�ܣ�";
		else if (i == 2)
			message = "������δ��ʼ�������ʼ�����ٽ��д˲���!";
	}
	~Error(void) {};					// ��������	
	void Show() const					// ��ʾ�쳣��Ϣ
	{
		cout << message << endl;		// ��ʾ�쳣��Ϣ	
	}
};

class Game_of_life
{
protected:
	char **cell;
	int numOfRow;
	int numOfCol;
	int generation;
	bool ClearHelp();
public:
	Game_of_life();
	~Game_of_life();
	bool Read();
	bool Game();
	bool Display(int gen = 0);
};
