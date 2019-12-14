#ifndef _STRVEC_HPP_
#define _STRVEC_HPP_
#include"Header.h"
#include<utility>
//C++ Primer chapter 13 p651
class StrVec {
	allocator<string> alloc;
	string* elements;
	size_t size;
	size_t capacity;

	void free();
	void reallocate(size_t);
	void chk_n_alloc();
	string* alloc_n_copy(const string*, size_t);
public:
	StrVec() :elements(nullptr), size(0), capacity(0) {}
	StrVec(initializer_list<string>);
	StrVec(const StrVec&);
	StrVec(StrVec&&)noexcept;
	StrVec& operator=(StrVec&&)noexcept;
	StrVec& operator=(const StrVec&);
	StrVec& operator=(initializer_list<string>);
	~StrVec();
	void push_back(const string&);
	void push_back(string&&);
	inline size_t getSize()const;
	inline size_t getCapacity()const;
	void reserve(size_t);
	void resize(size_t);
	const string* cbegin()const;
	const string* cend()const;
	string& at(size_t);
	string& operator[](size_t);
	const string& operator[](size_t)const;
	friend bool operator==(const StrVec&, const StrVec&);
	friend bool operator!=(const StrVec&, const StrVec&);
	friend bool operator<(const StrVec&, const StrVec&);
};




string& StrVec::operator[](size_t s) {
	if (s >= size)
		throw out_of_range("suscript out of range");
	return *(elements + s);
}
const string& StrVec::operator[](size_t s)const {
	if (s >= size)
		throw out_of_range("suscript out of range");
	return *(elements + s);
}
StrVec& StrVec::operator=(initializer_list<string> a) {
	auto temp = alloc_n_copy(a.begin(), a.size);
	free();
	elements = temp;
	size = capacity = a.size;
}
bool operator<(const StrVec& a, const StrVec& b) {
	if (a.size < b.size)
		return true;
	else if (a.size == b.size) {
		return lexicographical_compare(a.elements, a.elements + a.size,
			b.elements, b.elements + b.size);
	}
	else
		return false;
}
bool operator!=(const StrVec& a, const StrVec& b) {
	return !(a == b);
}
bool operator==(const StrVec& a, const StrVec& b) {
	if (a.size != b.size)
		return false;
	else {
		return equal(a.elements, a.elements + a.size, b.elements);
	}
}
void StrVec::push_back(string&& move) {
	chk_n_alloc();
	alloc.construct(elements + size, std::move(move));
	++size;
}
StrVec& StrVec::operator=(StrVec&& copy)noexcept {
	if (&copy != this) {
		free();
		elements = copy.elements;
		size = copy.size;
		capacity = copy.capacity;
		copy.elements = nullptr;
		copy.size = 0;
		copy.capacity = 0;
	}
	return *this;
}
StrVec::StrVec(StrVec&& copy)noexcept :elements(copy.elements),
size(copy.size), capacity(copy.capacity) {
	copy.elements = nullptr;
	copy.size = copy.capacity = 0;
}
string& StrVec::at(size_t loc) {
	if (loc >= size)
		throw runtime_error("subscript out of size");
	return *(elements + loc);
}
StrVec::StrVec(initializer_list<string> ini) {
	elements = alloc.allocate(ini.size());
	size = 0;
	for (const auto& i : ini) {
		alloc.construct(elements+size++, i);
	}
	capacity = size;
}
void StrVec::resize(size_t s) {
	reallocate(s);
}
void StrVec::reserve(size_t s) {
	reallocate(s);
}
StrVec::~StrVec() {
	free();
}
StrVec& StrVec::operator=(const StrVec& copy) {
	if (&copy != this) {
		free();
		elements = alloc_n_copy(copy.elements, copy.size);
		size = copy.size;
		capacity = copy.capacity;
	}
	return *this;
}
StrVec::StrVec(const StrVec& copy) {
	elements =alloc_n_copy(copy.cbegin(), copy.getSize());
	size = copy.size;
	capacity = copy.capacity;
}
string* StrVec::alloc_n_copy(const string* a, size_t s) {
	auto data = alloc.allocate(s);
	uninitialized_copy(a, a + s, data);
	return data;
}
void StrVec::reallocate(size_t newcapacity) {
	auto newdata = alloc.allocate(newcapacity);
	auto elem = elements;
	auto size_temp = size;
	if (elements) {
		//uninitialized_copy(make_move_iterator(cbegin()),
		//	make_move_iterator(cend()), newdata);
//#if 0
		for (size_t i = 0; i != size_temp; ++i) {
			//alloc.construct(newdata+i,*(elem+i));
			alloc.construct(newdata + i, std::move(*(elem + i)));
		}
//#endif
		free();
	}
	elements = newdata;
	capacity = newcapacity;
	size = size_temp;
}
void StrVec::free() {
	if (elements) {
		for_each(elements, elements + size,
			[&](string& pos) {alloc.destroy(&pos); });
		alloc.deallocate(elements, capacity);
		elements= nullptr;
		size = capacity = 0;
	}
}
size_t StrVec::getCapacity()const {
	return capacity;
}
size_t StrVec::getSize()const {
	return size;
}
const string* StrVec::cend()const {
	return elements+size;
}
const string* StrVec::cbegin()const {
	return elements;
}
void StrVec::push_back(const string& s) {
	chk_n_alloc();
	alloc.construct(elements+size, s);
	++size;
}
void StrVec::chk_n_alloc() {
	if (size == 0)
		reallocate(1);
	else if (size == capacity)
		reallocate(2*capacity);
}

#endif // !_STRVEC_HPP
