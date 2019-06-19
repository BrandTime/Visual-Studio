#ifndef  _MESSAGE_AND_FOLDER_HPP_
#define  _MESSAGE_AND_FOLDER_HPP_
#include"Header.h"
//C++ Primer chapter 13 p646
class Folder;
class Message {
	string contents;
	set<Folder *> folders;
	
	void move_folders(Message *);
	void add_to_folder(const Message&);
	void remove_from_folder(const Message&);
public:
	explicit Message(const string&);
	Message(const Message&);
	Message(Message&&);
	Message& operator=(Message&&);
	Message& operator=(const Message&);
	~Message();

	void save(Folder&);
	void remove(Folder&);
	void add_folder(Folder&);
	void remove_folder(Folder&);
	inline friend void swap( Message&, Message&);
};

class Folder {
	set<Message *> messages;

	void add_to_messages();
	void remove_from_messages();
public:
	explicit Folder(Message&);
	Folder(const Folder&);
	Folder& operator=(const Folder&);
	~Folder();
	void addMsg(Message&);
	void remMsg(Message&);
};






Message& Message::operator=(Message&& copy) {
	if (&copy != this) {
		remove_from_folder(*this);
		contents = std::move(copy.contents);
		move_folders(&copy);
	}
	return *this;
}
Message::Message(Message&& copy) {
	move_folders(&copy);
	contents = std::move(copy.contents);
}
void Message::move_folders(Message* m) {
	folders = std::move(m->folders);
	for (auto i : folders) {
		i->remMsg(*m);
		i->addMsg(*this);
	}
	m->folders.clear();
}
void Message::add_folder(Folder& f) {
	folders.insert(&f);
	save(f);
}
void Message::remove_folder(Folder& f) {
	folders.erase(&f);
	remove(f);
}
void Message::remove(Folder& f) {
	folders.erase(&f);
	f.remMsg(*this);
}
void Message::save(Folder& f) {
	folders.insert(&f);
	f.addMsg(*this);
}
void Message::add_to_folder(const Message& m) {
	for (auto f : folders) {
		f->addMsg(*this);
	}
}
void Message::remove_from_folder(const Message& m) {
	for (auto f : folders) {
		f->remMsg(*this);
	}
}
void swap(Message& a, Message& b) {
	a.remove_from_folder(a);
	b.remove_from_folder(b);
	swap(a.contents, b.contents);
	swap(a.folders, b.folders);
	a.add_to_folder(a);
	b.add_to_folder(b);
}
Message::Message(const string& str = "") :contents(str) {
	add_to_folder(*this);
}
Message::~Message() {
	remove_from_folder(*this);
}
Message& Message::operator=(const Message& copy) {
	if (&copy != this) {
		remove_from_folder(*this);
		contents = copy.contents;
		folders = copy.folders;
		add_to_folder(*this);
	}
	return *this;
}
Message::Message(const Message& m) :contents(m.contents) {
	folders = m.folders;
	add_to_folder(*this);
}
Folder::Folder(Message& m) {
	messages.insert(&m);
}
void Folder::addMsg(Message& m) {
	messages.insert(&m);
}
void Folder::remMsg(Message& m) {
	messages.erase(&m);
}
Folder::~Folder() {
	remove_from_messages();
}
Folder& Folder::operator=(const Folder& copy) {
	if (&copy != this) {
		remove_from_messages();
		messages = copy.messages;
		add_to_messages();
	}
	return *this;
}
Folder::Folder(const Folder& copy) :messages(copy.messages) {
	add_to_messages();
}
void Folder::add_to_messages() {
	for (auto i : messages) {
		i->save(*this);
	}
}
void Folder::remove_from_messages() {
	for (auto i : messages) {
		i->remove(*this);
	}
}

#endif // ! _MESSAGE_AND_FOLDER_HPP_