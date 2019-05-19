#include"Header.h"
#include"TestQuery.h"

int main() {
	fstream in("output1.txt", ios::in);
	if (!in) {
		cerr << "file open fail" << endl;
	}
	runQuery(in);
	in.close();

	system("pause");
	return 0;
}