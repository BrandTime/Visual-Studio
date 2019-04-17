#include<iostream>
#include<vector>
using namespace std;

//Ax^2+Bx^2+Cx^2+D=0
class QuadraticEquation {
private:
	double m_a;
	double m_b;
	double m_c;
public:
	QuadraticEquation(double a = 0, double b = 0, double c = 0) :
		m_a(a), m_b(b), m_c(c) {};
	~QuadraticEquation() {}
	double getDelta() {
		return pow(m_b, 2) - 4 * m_a*m_c;
	}
	void getRoot(vector<double>& root) {
		root.clear();
		double temp1 = -m_b + sqrt(getDelta()),
			temp2 = -m_b - sqrt(getDelta());
		if (getDelta() == 0) {
			root.push_back(temp1 / 2 / m_a);
		}
		else if (getDelta() > 0) {
			root.push_back(temp1 / 2 / m_a);
			root.push_back(temp2 / 2 / m_a);
		}
	}
};
void print(vector<double>& r) {
	for (auto i : r)
		cout << i << ends;
	cout << endl;
}
int main(void) {
	vector<double> root;
	QuadraticEquation first(1, 2, 1), second(2, 5, 2), third(1, 1, 1);
	first.getRoot(root);
	print(root);
	second.getRoot(root);
	print(root);
	third.getRoot(root);
	print(root);

	system("pause");
	return 0;
}