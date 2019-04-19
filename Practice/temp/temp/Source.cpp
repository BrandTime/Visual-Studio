#if 0
#include<iostream>
#include<string>
using namespace std;

int main(void) {
	string s = "1234";
	auto i = s.begin() + 1;
	i = s.insert(i, '8');
	cout << *i << endl;

	system("pause");
	return 0;
}
#endif