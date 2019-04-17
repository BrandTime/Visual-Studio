#if 0
#include"expression_greenday.h"
#include"expression_textbook.h"
#include"lk_bin_tree.h"

void visit(const double &elem) {
	cout << elem;
	return;
}
int main(void) {
	try {
		double eee;
		cin >> eee;
		cout << eee << endl;
	}
	catch (runtime_error& err) {
		cout << err.what() << endl;
	}

	system("PAUSE");
	return 0;
}
#endif