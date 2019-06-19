#ifndef _SECOND_H_
#define _SECOND_H_
#include"Header.h"
class Sales_data {
private:
	string ISBN;
	double avePrice;
	int saleNumber;
public:
	explicit Sales_data(string isbn = "", double ave = 0.0, int num = 0) :
		ISBN(isbn), avePrice(ave), saleNumber(num) {}
	Sales_data& operator=(const string&);
	string getISBN()const { return ISBN; }
	double getPrice()const { return avePrice; }
	int getCopies()const { return saleNumber; }
	void setISBN(string set) { ISBN = set; }
	void setPrice(double price) { avePrice = price; }
	void addSales(int i = 1) { saleNumber += i; }
	void operator+=(const Sales_data&);
	friend Sales_data operator+(const Sales_data&,const Sales_data&);
	friend istream& operator>>(istream& in, Sales_data& ob);
	friend ostream& operator<<(ostream& out, const Sales_data& ob);
};


Sales_data& Sales_data::operator=(const string& isbn) {
	ISBN = isbn;
	avePrice = 0;
	saleNumber = 0;
}
void Sales_data::operator+=(const Sales_data& a) {
	auto newAvePrice= (a.avePrice*a.saleNumber + avePrice*saleNumber) /
		(a.saleNumber + saleNumber);
	avePrice = newAvePrice;
	saleNumber += a.saleNumber;
}
Sales_data operator+(const Sales_data& a,const Sales_data& b) {
	double ave_price = (a.avePrice*a.saleNumber + b.avePrice*b.saleNumber) /
		(a.saleNumber + b.saleNumber);
	Sales_data temp(a.ISBN, ave_price, a.saleNumber + b.saleNumber);
	return temp;
}
ostream& operator<<(ostream& out, const Sales_data& ob) {
	out << "ISBN: " << ob.ISBN << ends << "avePrice: " << ob.avePrice << ends
		<< "saleNumber: " << ob.saleNumber << ends;
	return out;
}
istream& operator>>(istream& in, Sales_data& ob) {
	in >> ob.ISBN >> ob.avePrice >> ob.saleNumber;
	if (!in) {
		ob = Sales_data();
	}
		
	return in;
}

bool checkSize(const string& s, string::size_type sz) {
	return s.size() <= sz;
}
void elimDups(vector<string> &words) {
	sort(words.begin(), words.end());
	auto uni_iter = unique(words.begin(), words.end());
	words.erase(uni_iter, words.end());
}
void biggies(vector<string> &words, vector<string>::size_type sz) {
	elimDups(words);
	//print(words);
	stable_sort(words.begin(), words.end(), [](const string& a, const string& b)->bool {
		return a.size() < b.size();
	});
	auto wc = stable_partition(words.begin(), words.end(),
		bind(checkSize, _1, sz));
	int count = count_if(wc, words.end(),
		bind(checkSize, _1, sz));
	cout << "There are " << count << "words" << endl;
	for_each(wc, words.end(), [](const string& str) {
		cout << str << endl;
	});
}
bool compareIsbn(const Sales_data& first, const Sales_data& second) {
	return first.getISBN() < second.getISBN();
}
const string& transform(const string& s,
	const unordered_map<string, string>& trans_map) {
	auto iter = trans_map.find(s);
	if (iter == trans_map.end())
		return s;
	else
		return iter->second;
}
unordered_map<string, string> buildMap(fstream& in) {
	unordered_map<string, string> trans_map;
	string key, value;
	while (in >> key && getline(in, value)) {
		if (value.size() > 1)
			trans_map[key] = value.substr(1);
		else
			throw runtime_error("No rule for " + key);
	}
	return trans_map;
}
void word_transform(fstream& words, fstream& map_file) {
	unordered_map<string, string> trans_map = buildMap(map_file);
	string line, word;
	bool firstWord = true;
	while (words >> word) {
		if (!firstWord)
			cout << ends;
		else
			firstWord = false;
		cout << transform(word, trans_map);
	}
	cout << endl;
}
shared_ptr<vector<int>> first() {
	return make_shared<vector<int>>();
}
void second(shared_ptr<vector<int>> ivec) {
	int i;
	while (cin >> i)
		ivec->push_back(i);
}
void third(shared_ptr<vector<int>> ivec) {
	for (const auto& i : *ivec)
		cout << i << endl;
}
#endif // ! _SECOND_H_