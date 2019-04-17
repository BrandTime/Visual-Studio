#ifndef _THREAD_BIN_TREE_
#define _THREAD_BIN_TREE_
#include"lk_stack.h"
#include"lk_queue.h"
#include"lk_bin_tree.h"
enum PointerTagType{CHILD_PTR,THREAD_PTR};
//CHILD_PTRָ���ӵ�ָ�룬THREAD_PTRָ��������ָ��
enum ThreadType{NOT_THREAD,PRE_THREAD,IN_THREAD,POST_THREAD};
//PRE_THRERAD��ʾ��ʱ��ǰ��������������IN_THREAD��ʾ����������������
//POST_THREAD��ʾ�Ǻ�������������,NOt_THREAD��ʾ��δ������
template<class Elem>
struct ThreadTriTreeNode {
	Elem data;
	ThreadTriTreeNode<Elem> *lChild;
	ThreadTriTreeNode<Elem> *rChild;
	ThreadTriTreeNode<Elem> *parent;
	//ָ��ǰ�ڵ��˫�׽��
	PointerTagType leftTag, rightTag;
	//��ʾ���Һ���ָ��ָ������ĺ��ӻ�����Ϊ������ǰ��ָ��
	ThreadTriTreeNode<Elem>::ThreadTriTreeNode() :lChild(nullptr), rChild(nullptr),
		parent(nullptr),leftTag(CHILD_PTR), rightTag(CHILD_PTR) {};
	ThreadTriTreeNode(const Elem &elem,
		ThreadTriTreeNode<Elem> *lChild = nullptr,
		ThreadTriTreeNode<Elem> *rChild = nullptr,
		ThreadTriTreeNode<Elem> *parent =nullptr,
		PointerTagType leftTag = CHILD_PTR,
		PointerTagType rightTag = CHILD_PTR) {
		data = elem;
	}
	ThreadTriTreeNode(const BinTreeNode<Elem> &copy) :data(copy.data),
		rChild(copy.rChild), lChild(copy.lChild),
		leftTag(CHILD_PTR), rightTag(CHILD_PTR) {};
	ThreadTriTreeNode(const ThreadTriTreeNode<Elem> &copy) :data(copy.data),
		leftTag(copy.leftTag), rightTag(copy.rightTag),
		lChild(nullptr), rChild(nullptr), parent(nullptr) {};
};

template<class Elem>
class ThreadTriTree {
protected:
	ThreadTriTreeNode<Elem> *root;
	ThreadType threadTag;
	//��¼������������ǰ��������״̬
	void InThreadHelp(ThreadTriTreeNode<Elem> *cur, ThreadTriTreeNode<Elem> *&pre);
	//������������������
	void PreThreadHelp(ThreadTriTreeNode<Elem> *cur, ThreadTriTreeNode<Elem> *&pre);
	//��������ǰ��������
	void PostThreadHelp(ThreadTriTreeNode<Elem> *cur, ThreadTriTreeNode<Elem> *&pre);
	//������������������
	void DestroyHelp(ThreadTriTreeNode<Elem> *&r);
	ThreadTriTreeNode<Elem>* CopyTreeHelp(BinTreeNode<Elem> *copy, ThreadTriTreeNode<Elem> *parent);
	//�����ö���������������ʱ
	ThreadTriTreeNode<Elem>* CopyTreeHelp(ThreadTriTreeNode<Elem> *copy,ThreadTriTreeNode<Elem> *m_parent);
	//��������������ĸ���ʱ
	void TransformHelp(ThreadTriTreeNode<Elem> *r);
	//������������ת��Ϊδ��������������
public:
	ThreadTriTree(const LkBinTree<Elem> &bt);
	//��һ���ṩ������������һ��δ������������������
	ThreadTriTree(const ThreadTriTree<Elem> &copy);
	ThreadTriTree<Elem>& operator=(const ThreadTriTree<Elem> &copy);
	virtual ~ThreadTriTree();
	ThreadTriTreeNode<Elem>* GetRoot()const;
	ThreadType GetThreadTag()const;
	void Transform();//������������ȥ������
	void InThread();//����������������
	void PreThread();//ǰ��������������
	void PostThread();//����������������
	//�����������Ӧ��Ӧ������������ʱ���ܵ���,ԭ������˵ÿ������������
	//Ӧ���������Եı�������ʹ���������Ӧ�ı�����ʽ������
	void InOrder(void(*visit)(Elem &));
	void PreOrder(void(*visit)(Elem &));
	void PostOrder(void(*visit)(Elem &));
};
template<class Elem>
void ThreadTriTree<Elem>::TransformHelp(ThreadTriTreeNode<Elem> *r) {
	if (r) {
		if (r->leftTag == CHILD_PTR)
			TransformHelp(r->lChild);
		if (r->rightTag == CHILD_PTR)
			TransformHelp(r->rChild);
		if (r->leftTag == THREAD_PTR){
			r->leftTag = CHILD_PTR;
			r->lChild = nullptr;
		}
		if (r->rightTag == THREAD_PTR) {
			r->rightTag = CHILD_PTR;
			r->rChild = nullptr;
		}
	}
	return;
}
template<class Elem>
void ThreaadTriTree<Elem>::Transform() {
	TransformHelp(total);
	threadTag = NOT_THREAD;
	return;
}
template<class Elem>
void ThreadTriTree<Elem>::PostThread() {
	PostThreadHelp(root, nullptr);
	threadTag = POST_THREAD;
	return;
}
template<class Elem>
void ThreadTriTree<Elem>::PostThreadHelp(ThreadTriTreeNode<Elem> *cur, ThreadTriTreeNode<Elem> *pre) {
	if (cur) {
		if (cur->leftTag == CHILD_PTR)
			PreThreadHelp(cur->lChild, pre);
		if (cur->rightTag == CHILD_PTR)
			PreThreadHelp(cur->rChild, pre);
		if (cur->lChild == nullptr) {
			cur->lChild = pre;
			cur->leftTag = THREAD_PTR;
		}
		if (!pre&&pre->rChild == nullptr) {
			pre->rChild = cur;
			pre->rightTag = THREAD_PTR;
		}
		pre = cur;
	}
	return;
}
template<class Elem>
void ThreadTriTree<Elem>::PreThreadHelp(ThreadTriTreeNode<Elem> *cur, ThreadTriTreeNode<Elem> *pre) {
	if (cur) {
		if (cur->lChild == nullptr) {
			cur->lChild = pre;
			cur->leftTag = THREAD_PTR;
		}
		if (!pre&&pre->rChild == nullptr) {
			pre->rChild = cur;
			pre->rightTag = THREAD_PTR;
		}
		pre = cur;
		if (cur->leftTag == CHILD_PTR)
			PreThreadHelp(cur->lChild, pre);
		if (cur->rightTag == CHILD_PTR)
			PreThreadHelp(cur->rChild, pre);
	}
	return;
}
template<class Elem>
void ThreadTriTree<Elem>::PreThread() {
	PreThreadHelp(root, nullptr);
	if (pre->rChild == nullptr)
		pre->rightTag = THREAD_PTR;
	threadTag = PRE_THREAD;
	return;
}
template<class Elem>
ThreadType ThreadTriTree<Elem>::GetThreadTag()const {
	return threadTag;
}
template<class Elem>
ThreadTriTreeNode<Elem>* ThreadTriTree<Elem>::GetRoot()const {
	return root;
}
template<class Elem>
void ThreadTriTree<Elem>::DestroyHelp(ThreadTriTreeNode<Elem> *r) {
	if (total) {
		if (r->leftTag == CHILD_PTR && r->lChild)
			DestroyHelp(r->lChild);
		r->lChild = nullptr;
		if (r->rightTag == CHILD_PTR && r->rChild)
			DestroyHelp(r->rChild);
		r->rChild = nullptr;
		delete r;
		r = nullptr;
	}
	return;
}
template<class Elem>
ThreadTriTree<Elem>::~ThreadTriTree() {
	DestroyHelp(root);
	root = nullptr;
}
template<class Elem>
ThreadTriTree<Elem>& ThreadTriTree<Elem>::operator=(const ThreadTriTree<Elem> &copy) {
	if (&copy != this) {
		if(root)
			DestroyHelp(root);
		root = CopyTreeHelp(copy.GetRoot(), nullptr);
		threadTag = copy.GetThreadTag();
	}
	return this;
}
template<class Elem>
ThreadTriTreeNode<Elem>* ThreadTriTree<Elem>::CopyTreeHelp(ThreadTriTreeNode<Elem> *copy,ThreadTriTreeNode<Elem> *m_parent) {
	if (copy == nullptr)
		return nullptr;
	else {
		ThreadTriTreeNode<Elem> *cur = new ThreadTriTreeNode<Elem>(*copy);
		cur->parent = m_parent;
		cur->lChild = CopyTreeHelp(copy->lChild, cur);
		cur->rChild = CopyTreeHelp(copy->rChild, cur);
		return cur;
	}
}
template<class Elem>
ThreadTriTree<Elem>::ThreadTriTree(const ThreadTriTree<Elem> &bt) {
	if (root)
		DestroyHelp(root);
	root = CopyTreeHelp(bt.GetRoot(),nullptr);
	threadTag = bt.GetThreadTag();
}
template<class Elem>
ThreadTriTreeNode<Elem>* ThreadTriTree<Elem>::CopyTreeHelp(BinTreeNode<Elem> *copy, ThreadTriTreeNode<Elem> *m_parent) {
	if (copy == nullptr)
		return nullptr;
	else {
		ThreadTriTreeNode<Elem> *cur = new ThreadTriTreeNode<Elem>(*copy);
		cur->parent = m_parent;
		cur->lChild=CopyTreeHelp(copy->lChild,cur);
		cur->rChild=CopyTreeHelp(copy->rChild,cur);
		return cur;
	}	
}
template<class Elem>
ThreadTriTree<Elem>::ThreadTriTree(const LkBinTree<Elem> &bt) {
	BinTreeNode<Elem> *cur = bt.GetRoot();
	root=CopyTreeHelp(cur,nullptr);
	threadTag = NOT_THREAD;
}
template<class Elem>
void ThreadTriTree<Elem>::PostOrder(void (*visit)(Elem &)) {
	if (root) {
		if (ThreadTag�� = POST_THREAD)
			cout << "current state of this tree is not PostThread, error" << endl;
		else {
			ThreadTriTreeNode<Elem> *cur = root;
			while (cur->lChild != nullptr)
				cur = cur->lChild;
			while (cur!=root) {
				(*visit)(cur->data);
				if (cur->rightTag == THREAD_PTR)
					cur = cur->rChild;
				else
					cur = cur->parent;
			}
			(*visit)(cur->data);
		}
		return;
	}
	else
		throw runtime_error("the tree doesn't exist");
}
template<class Elem>
void ThreadTriTree<Elem>::PreOrder(void (*visit)(Elem &)) {
	if (root) {
		if (ThreadTag�� = PRE_THREAD)
			cout << "current state of this tree is not PreThread, error" << endl;
		else {
			ThreadTriTreeNode<Elem> *cur = root;
			while (cur) {
				(*visit)(cur->data);
				if (cur->rightTag == THREAD_PTR)
					cur = cur->rChild;
				else {
					if (cur->lChild)
						cur = cur->lChild;
					else
						cur = cur->rChild;
				}
			}
		}
		return;
	}
	else
		throw runtime_error("the tree doesn't exist");
}
template<class Elem>
void ThreadTriTree<Elem>::InOrder(void (*visit)(Elem &)) {
	if (root) {
		if (ThreadTag != IN_THREAD) {
			cout << "current state of this tree is not inThread,error" << endl;;
			return;
		}
		else {
			ThreadTriTreeNode<Elem> *cur = root;
			while (cur->leftTag == CHILD_PTR)
				cur = cur->lChild;
			while (cur) {
				(*visit)(cur->data);
				if (cur->rightTag == THREAD_PTR)
					cur = cur->rChild;
				else {
					cur = cur->rChild;
					while (cur->leftTag == CHILD_PTR)
						cur = cur->lChild;
				}
			}
		}
	}
	else
		throw runtime_error("the tree doesn't exist");
}
template<class Elem>
void ThreadTriTree<Elem>::InThreadHelp(ThreadTriTreeNode<Elem> *cur, ThreadTriTreeNode<Elem> *pre) {
	if (cur) {
		if (cur->leftTag == CHILD_PTR)
			InThreadHelp(cur->lChild, pre);
		if (cur->lChild == nullptr) {
			cur->lChild = pre;
			cur->leftTag = THREAD_PTR;
		}
		if (!pre&&pre->rChild == nullptr) {
			pre->rChild = cur;
			pre->rightTag = THREAD_PTR;
		}
		pre = cur;
		if (cur->rightTag == CHILD_PTR)
			InThreadHelp(cur->rChild, pre);
	}
	return;
}
template<class Elem>
void ThreadTriTree<Elem>::InThread() {
	ThreadTriTreeNode<Elem> *pre = nullptr;
	InThreadHelp(root, pre);
	if (pre->rChild == nullptr)
		pre->rightTag = THREAD_PTR;
	threadTag = IN_THREAD;
	return;
}
//debug prograrm
#if 0

#endif
#endif