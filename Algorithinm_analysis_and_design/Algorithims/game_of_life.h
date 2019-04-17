#pragma once
#include<iostream>
#include<string>
#include<cstdio>
using namespace std;

#define OCCUPIED 1
#define UNOCCUPIED 0
#define MAX_ERROR_MESSAGE_LEN 100

// 通用异常类                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
class Error
{
private:
	// 数据成员
	string message;// 异常信息

public:
	//  方法声明
	Error(string mes = "一般性异常!")	// 构造函数 
	{
		message = mes;		// 复制异常信息
	}
	Error(int i) {
		if (i == 1)
			message = "内存空间不足，分配内存失败！";
		else if (i == 2)
			message = "生命并未初始化，请初始化后再进行此操作!";
	}
	~Error(void) {};					// 析构函数	
	void Show() const					// 显示异常信息
	{
		cout << message << endl;		// 显示异常信息	
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
