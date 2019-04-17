#include"class.h"

int main(void)
{
	Info a;

	a.SetC();
	a.ShowC();
	a.SetF();
	cout << "接下来进行第 1 学年成绩的输入：" << endl;
	a.AddS(1);
	a.AddS(1);
	a.AddS(1);
	cout << "输入第二学年的成绩：" << endl;
	a.AddS(2);
	a.AddS(2);
	a.AddS(2);
	a.Showall();

	return 0;
}