#include"class.h"

int main(void)
{
	Info a;

	a.SetC();
	a.ShowC();
	a.SetF();
	cout << "���������е� 1 ѧ��ɼ������룺" << endl;
	a.AddS(1);
	a.AddS(1);
	a.AddS(1);
	cout << "����ڶ�ѧ��ĳɼ���" << endl;
	a.AddS(2);
	a.AddS(2);
	a.AddS(2);
	a.Showall();

	return 0;
}