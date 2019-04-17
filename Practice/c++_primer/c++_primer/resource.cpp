#include"first.h"
#include"second.h"

StrBlob::StrBlob() :data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il) :
	data(make_shared<vector<string>>(il)) {}
void StrBlob::check(size_type i, const string& msg)const {
	if (i >= data->size())
		throw out_of_range(msg);
}
void StrBlob::pop_back() {
	check(0, "Pop_back on empty StrBlob");
	data->pop_back();
}
string& StrBlob::front() {
	check(0, "front on empty StrBlob");
	return data->front();
}
string& StrBlob::back() {
	check(0, "back on empty StrBlob");
	return data->back();
}
StrBlobPtr StrBlob::begin()const {
	return StrBlobPtr(*this); 
}
StrBlobPtr StrBlob::end()const {
	return StrBlobPtr(*this, data->size()); 
}
StrBlobPtr& StrBlobPtr::incr() {
	check(curr, "increment past end");
	++curr;
	return *this;
}
string& StrBlobPtr::deref()const {
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}
shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string& msg)const {
	auto ret = wptr.lock();
	if (!ret)
		throw runtime_error("unbounded StrBlobPtr");
	if (i >= ret->size())
		throw out_of_range(msg);
	return ret;
}
bool operator==(const StrBlobPtr& first,
	const StrBlobPtr& second) {
	auto first_p = first.check(0),
		second_p = second.check(0);
	if (first_p == second_p&&first.curr==second.curr)
		return true;
	else
		return false;
}
bool operator!=(const StrBlobPtr& first,
	const StrBlobPtr& second) {
	auto first_p = first.check(0),
		second_p = second.check(0);
	if (first_p != second_p||first.curr!=second.curr)
		return true;
	else
		return false;
}




Sales_data& Sales_data::operator+(const Sales_data& s) {
	Sales_data* temp = new Sales_data(this->ISBN, this->avePrice,
		this->saleNumber + s.getCopies());
	return *temp;
}
ostream& operator<<(ostream& out, const Sales_data& ob) {
	out << "ISBN: " << ob.ISBN << ends << "avePrice: " << ob.avePrice << ends
		<< "saleNumber: " << ob.saleNumber << ends;
	return out;
}
istream& operator>>(istream& in, Sales_data& ob) {
	in >> ob.ISBN >> ob.avePrice >> ob.saleNumber;
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