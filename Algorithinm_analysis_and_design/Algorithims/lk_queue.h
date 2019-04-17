#ifndef _LK_QUEUE_
#define _LK_QUEUE_
template<class Elem>
struct lkqNode {
	Elem data;
	lkqNode<Elem> *next;

	lkqNode() :next(nullptr) {};
	lkqNode(const Elem &elem, lkqNode<Elem> *m_next = nullptr) {
		data = elem;
		next = m_next;
	}
};
template<class Elem>
class Lk_queue {
protected:
	lkqNode<Elem> *head, *rear;
	int length;
	void Init();
public:
	Lk_queue();
	Lk_queue(const Elem &elem);
	Lk_queue(const Lk_queue<Elem> &copy);
	Lk_queue<Elem>& operator=(const Lk_queue<Elem> &copy);
	virtual ~Lk_queue();
	void Clear();
	int Get_length()const;
	bool Empty()const;
	bool Out_queue(Elem &elem);
	bool In_queue(Elem &elem);
	bool Get_head(Elem &elem);
	void Traverse(void(*visit)(Elem &));
};
//
//the specification of the class
template<class Elem>
void Lk_queue<Elem>::Traverse(void(*visit)(Elem &)) {
	if (!head)
		throw runtime_error("the queue is empty, cannot display");
	for (auto temp = rear; temp; temp = temp->next)
		(*visit)(temp->data);
	return;
}
template<class Elem>
bool Lk_queue<Elem>::Get_head(Elem &elem) {
	if (!head)
		return false;
	elem = head->data;
	return true;
}
template<class Elem>
bool Lk_queue<Elem>::In_queue(Elem &elem) {
	auto temp = new lkqNode<Elem>(elem);
	if (!temp)
		return false;
	if (length)
		rear->next = temp;
	rear = temp;
	if (!head)
		head = temp;
	++length;
	return true;
}
template<class Elem>
bool Lk_queue<Elem>::Out_queue(Elem &elem) {
	if (!head)
		return false;
	elem = head->data;
	auto temp = head->next;
	delete head;
	head = temp;
	length = (length == 0) ? 0 : (length - 1);
	return true;
}
template<class Elem>
bool Lk_queue<Elem>::Empty()const {
	return length == 0;
}
template<class Elem>
int Lk_queue<Elem>::Get_length()const {
	return length;
}
template<class Elem>
void Lk_queue<Elem>::Clear() {
	Elem temp;
	while (head)
		Out_queue(temp);
	head = rear = nullptr;
	length = 0;
}
template<class Elem>
Lk_queue<Elem>::~Lk_queue() {
	Clear();
}
template<class Elem>
Lk_queue<Elem>& Lk_queue<Elem>::operator=(const Lk_queue<Elem> &copy) {
	if (&copy != this) {
		if (length)
			Clear();
		Init();
		for (auto temp = copy.rear; temp != nullptr; temp = temp->next)
			In_queue(temp->data);
	}
	return *this;
}
template<class Elem>
Lk_queue<Elem>::Lk_queue(const Lk_queue<Elem> &copy) {
	if (length)
		Clear();
	Init();
	for (auto temp = copy.rear; temp != nullptr; temp = temp->next)
		In_queue(temp->data);
}
template<class Elem>
Lk_queue<Elem>::Lk_queue(const Elem &elem) {
	Init();
	In_queue(elem);
}
template<class Elem>
Lk_queue<Elem>::Lk_queue() {
	Init();
}
template<class Elem>
void Lk_queue<Elem>::Init() {
	head = nullptr, rear = nullptr, length = 0;
	return;
}


//debug program
#if 0
int main(void) {

	system("PAUSE");
	return 0;
}
#endif
#endif // !_LK_QUEUE_


