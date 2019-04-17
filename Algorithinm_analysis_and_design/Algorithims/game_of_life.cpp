#include"game_of_life.h"
Game_of_life::Game_of_life() {
	cell = nullptr;
}
Game_of_life::~Game_of_life() {
	ClearHelp();
}
bool Game_of_life::ClearHelp() {
	if (cell == nullptr)
		return true;
	for (int i = 0; i < numOfRow; i++)
		delete[]cell[i];
	delete[]cell;
	cell = nullptr;
	return true;
}
bool Game_of_life::Display(int gen) {
	if (cell == nullptr)
		return false;
	cout << "+";
	for (int i = 0; i < numOfCol; i++)
		cout << "-";
	cout << "+" << endl;

	for (int i = 0; i < numOfRow; i++) {
		cout << "|";
		for (int j = 0; j < numOfCol; j++)
			cout << ((cell[i][j] == OCCUPIED) ? '*' : ' ');
		cout << "|" << endl;
	}

	cout << "+";
	for (int i = 0; i < numOfCol; i++)
		cout << "-";
	cout << "+" << endl;
	return true;
}
bool Game_of_life::Read() {
	cout << "���������������� ���� ����������" << endl;
	cin >> numOfRow >> numOfCol >> generation;
	if (numOfRow <= 0)
		throw Error("��������ӦΪ����");
	if (numOfCol <= 0)
		throw Error("��������ӦΪ����");
	if (generation <= 0)
		throw Error("����������ӦΪ������");
	ClearHelp();

	int i = 0, j = 0;
	cell = new char*[numOfRow];
	if (!cell)
		throw Error(1);
	for (i = 0; i < numOfRow; i++) {
		cell[i] = new char[numOfCol];
		if (!cell[i])
			throw Error(1);
	}
	for (i = 0; i < numOfRow; i++)
		for (int j = 0; j < numOfCol; j++)
			cell[i][j] = UNOCCUPIED;

	string line;
	if (!cell)
		throw Error(1);
	int maxRow = 0;								// ���������к�
	int maxCol = 0;

	cout << "�������������ʼ״̬:" << endl;
	i = 0;
	getchar();
	while (i < numOfRow&&getline(cin, line)) {
		if (line.size() > 0
			&& line.size() > numOfCol)
			throw Error("����ĳ��Ȳ�Ӧ������������!");
		for (j = 0; j < line.size(); j++) {
			if (line[j] != ' ')
				cell[i][j] = OCCUPIED;
		}
		i++;
	}
	return true;
}
bool Game_of_life::Game() {
	if (!cell)
		throw Error(2);
	int i, j;
	int **nerb = new int*[numOfRow];
	for (i = 0; i < numOfRow; i++)
		nerb[i] = new int[numOfCol];

	for (int gen = 1; gen <= generation; gen++) {
		bool existlife = false;
		bool isstable = true;
		for (i = 0; i < numOfRow; i++)
			for (j = 0; j < numOfCol; j++) {
				nerb[i][j] = 0;
			}
		cout << "��" << gen << "��������" << endl;

		for (i = 0; i < numOfRow; i++)
			for (j = 0; j < numOfCol; j++) {

				int Top = (i == 0) ? i : i - 1;
				int Bottom = (i == numOfRow - 1) ? numOfRow - 1 : i + 1;
				int Left = (j == 0) ? j : j - 1;
				int Right = (j == numOfCol - 1) ? numOfCol - 1 : j + 1;

				for (int n = Top; n <= Bottom; n++)
					for (int m = Left; m <= Right; m++)
						if ((n != i || m != j) && cell[n][m] == OCCUPIED)
							nerb[i][j]++;
				if (cell[i][j] == UNOCCUPIED && nerb[i][j] == 3)
					isstable = false;
				if (cell[i][j] == OCCUPIED &&
					(nerb[i][j] != 3 && nerb[i][j] != 2))
					isstable = false;
			}
		for (i = 0; i < numOfRow; i++)
			for (j = 0; j < numOfCol; j++) {
				if (cell[i][j] == OCCUPIED) {
					if (nerb[i][j] != 3 && nerb[i][j] != 2)
						cell[i][j] = UNOCCUPIED;
					else
						existlife = true;
				}
				else  if (nerb[i][j] == 3) {
					cell[i][j] = OCCUPIED;
					existlife = true;
				}
			}
		Display(gen);
		if (existlife)
			if (isstable)
				cout << endl << "���������������ȶ�������������" << endl;
			else
				cout << endl << "�����彫ȫ������������������" << endl;
		system("PAUSE");
	}

	generation = numOfCol = numOfRow = 0;
	return true;
}

#if 0
//���Գ���
#include"game.h"

int main(void) {

	try {
		Game_of_life game;
		game.Read();
		game.Display();
		game.Game();
	}
	catch (Error err) {
		err.Show();
	}

#if 0
	string a("string");
	cout << a.size();
#endif
	system("PAUSE");
	return 0;
}
#endif