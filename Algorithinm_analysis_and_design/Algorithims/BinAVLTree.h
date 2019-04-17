#ifndef _BINAVLTREE_H_
#define _BINAVLTREE_H_
//平衡二叉树的实现
//采用java的命名惯例
#include"lk_queue.h"
#include"lk_stack.h"
static const int LEFT_HIGH = 1;//左高
static const int EAQUAL_HIGH = 0;//等高
static const int RIGHT_HIGH = -1;//右高

template<class Elem>
class BinAVLTreeNode {
protected:
	Elem data;
	int balanceFactor;//结点的平衡因子
	BinAVLTreeNode<Elem> *lChild;
	BinAVLTreeNode<Elem> *rChild;
public:
	BinAVLTreeNode();
	BinAVLTreeNode(const Elem &elem, int m_bf=EAQUAL_HIGH, 
		BinAVLTreeNode<Elem> *m_lChild=nullptr,BinAVLTreeNode<Elem> *m_rChild=nullptr);
	BinAVLTreeNode(const BinAVLTreeNode<Elem>& copy);
	BinAVLTreeNode<Elem>& operator=(const BinAVLTreeNode<Elem>& copy);
	~BinAVLTreeNode();
};

template<class Elem,class Key>
class BinAVLTree {
protected:
	BinAVLTreeNode<Elem> *root;

	BinAVLTreeNode<Elem>* copyHelp(const BinAVLTreeNode<Elem> *copy);
	void destroyHelp(BinAVLTreeNode<Elem> *r);
	void preOrderHelp(BinAVLTreeNode<Elem> *r);
	void inOrderHelp(BinAVLTreeNode<Elem> *r);
	void postORderHelp(BinAVLTreeNode<Elem> *r);
	void heightHelp(BinAVLTreeNode<Elem> *r);
	void nodeCountHelp(BinAVLTreeNode<Elem> *r);
	BinAVLTreeNode<Elem>* parentHelp(BinAVLTreeNode<Elem> *r, 
		const BinAVLTreeNode<Elem> *cur)const;
	BinAVLTreeNode<Elem>* searchHelp(const Key& key)const;
	//查找的辅助函数
	BinAVLTreeNode<Elem>* searchHelp( const Key& key,
		BinAVLTreeNode<Elem> *pa,Stack<BinAVLTreeNode<Elem>*> &s)const;
	//返回指向关键字为Key的元素的指针，用f返回其双亲，栈s存储查找路径
	void leftRotate(BinAVLTreeNode<Elem> *&subroot);
	void rightRotate(BinAVLTreeNode<Elem> *&subRoot);
	//对以subroot为根的二叉树做右旋处理，处理之后subrooot指向新的树根结点，
	//也就是旋转处理前的做子树的根节点
	void insertLeftBalance(BinAVLTreeNode<Elem> *&subRoot);
	void insertRightBalance(BinAVLTreeNode<Elem> *&subRoot);
	//对以subroot为根的二叉树插入时做平衡处理，处理后subroot指向新的树根结点
	void insertBalance(const Elem &elem, Stack<BinAVLTreeNode<Elem>*> &s);
	//从插入结点elem根据查找路径进行回溯，并作平衡处理
	void deleteLeftBalance(BinAVLTreeNode<Elem> *&subRoot, bool &isShorter);
	//对以subroot为根的二叉树删除时做左平衡处理，处理后subroot指向新的树根结点
	void deleteRightBalance(BinAVLTreeNode<Elem> *&subRoot, bool &isShorter);
	//对以subroot为根的二叉树删除时作右平衡处理，处理后subroot指向新的树根结点
	void deleteBalance(const Key& key, Stack<BinAVLTreeNode<Elem> *> &s);
	//从删除结点根据查找路径进行回溯，并作平衡处理
	void deleteHelp(const Key& key, BinAVLTreeNode<Elem> *&p, 
		Stack<BinAVLTreeNode<Elem>*> &s);
	//删除p指向的结点
public:
	BinAVLTree();
	BinAVLTree(const Elem& elem);//建立以e为根的树
	BinAVLTree(BinAVLTreeNode<Elem> *r);//以r为根构造AVL树
	BinAVLTree(const BinAVLTree<Elem,Key>& copy);
	BinAVLTree<Elem>& operator=(const BinAVLTree<Elem,Key>& copy);
	~BinAVLTreeNode();
	bool empty()const;
	bool getElem(BinAVLTreeNode<Elem> *cur, Elem &elem)const;
	bool setElem(BinAVLTreeNode<Elem> *cur, Elem &elem);
	BinAVLTreeNode<Elem>* getRoot()const;
	void inOrder(void(*visit)(const Elem&))const;
	void preOrder(void(*visit)(const Elem&))const;
	void postOrder(void(*visit)(const Elem&))const;
	void levelOrder(void(*visit)(const Elem&))const;
	int nodeCount()const;
	int getHeight()const;
	BinAVLTreeNode<Elem>* search(const Key &key);
	bool insertNode(const BinAVLTreeNode<Elem> &node);
	bool deleteNode(const BinAVLTreeNode<Elem> &node);
	BinAVLTreeNode<Elem>* getParent(const BinAVLTreeNode<Elem> *cur);
	BinAVLTreeNode<Elem>* getLeftChild(const BinAVLTreeNode<Elem> *cur);
	BinAVLTreeNode<Elem>* getRightChild(const BinAVLTreeNode<Elem> *cur);
};
template<class Elem, class Key>
void BinAVLTree<Elem, Key>::insertBalance(const Elem& elem, Stack<BinAVLTreeNode<Elem> *> &s) {
	bool isTaller = true;//stand for whether the height of subtree grows or not
	while (!s.Empty() && isTaller) {
		BinAVLTreeNode<Elem> *curNode, *parentNode;
		s.Pop(curNode);
		if (!s.Empty())
			parentNode = s.Top();
		else 
			parentNode = nullptr;
		if (elem < curNode->data) {
			
		}
		else {

		}
	}

	return;
}
template<class Elem, class Key>
bool BinAVLTree<Elem, Key>::insert(const Elem& elem) {
	BinAVLTreeNode<Elem> *f;
	Stack<BinAVLTreeNode<Elem> *> s;
	if (searchHelp(elem, f, s) == nullptr) {
		BinAVLTreeNode<Elem> *node = new BinAVLTreeNode<Elem>(elem);
		node->balanceFactor = EAQUAL_HIGH;
		if (elem < f->data)
			f->lChild = node;
		else
			f->rChild = node;
		insertBalance(elem, s);
		return true;
	}
	else
		return false;
}
template<class Elem, class Key>
void BinAVLTree<Elem, Key>::rightRotate(BinAVLTreeNode<Elem> *&subRoot) {
	if (subRoot) {
		BinAVLTreeNode<Elem> *ptrNode = subRoot->lChild;
		subRoot->lChild = ptrNode->rChild;
		ptrNode->rChild = subRoot;
		subRoot = ptrNode;
	}
	return;
}
template<class Elem, class Key>
void BinAVLTree<Elem, Key>::leftRotate(BinAVLTreeNode<Elem> *&subRoot) {
	if (subRoot) {
		BinAVLTreeNode<Elem> *ptrNode = subRoot->rChild;
		subRoot->rChild = ptrNode->lChild;
		ptrNode->lChild = subRoot;
		subRoot = ptrNode;
	}
	return;
}
template<class Elem, class Key>
BinAVLTreeNode<Elem>* BinAVLTree<Elem, Key>::searchHelp(const Key& key) const{
	Stack<BinAVLTreeNode<Elem>*> stack;
	BinAVLTreeNode<Elem> *temp, *result;
	return searchHelp(key, temp, stack);
}
template<class Elem, class Key>
BinAVLTreeNode<Elem>* BinAVLTree<Elem, Key>::searchHelp(const Key& key,
	BinAVLTreeNode<Elem> *pa, Stack<BinAVLTreeNode<Elem>*> &s) const{
	BinAVLTreeNode<Elem> *iter = getRoot();
	pa = nullptr;
	while (iter != nullptr&&iter->datea != key) {
		if (iter->data >= key) {
			pa = iter;
			s.Push(iter);
			iter = iter->rChild;
		}
		else {
			pa = iter;
			s.Push(iter);
			iter = iter->lChild;
		}
	}
	return iter;
}
template<class Elem,class Key>
BinAVLTree<Elem, Key>::BinAVLTree() {
	root = new BinAVLTreeNode<Elem>;
}
template<class Elem, class Key>
BinAVLTree<Elem, Key>::BinAVLTree(const Elem& elem) {
	root = new BinAVLTreeNode<Elem>(elem);
}
template<class Elem, class Key>
BinAVLTreeNode<Elem>* BinAVLTree<Elem, Key>::copyHelp(BinAVLTreeNode<Elem> *r) {
	if (r == nullptr)
		return nullptr;
	else {
		BinAVLTreeNode<Elem> *temp = new BinAVLTreeNode<Elem>(*r);
	}
}
template<class Elem, class Key>
BinAVLTree<Elem, Key>::BinAVLTree(const BinAVLTreeNode<Elem> *r) {
	root = copyHelp(r);
}
//
//
//
//
//
//
//
//the specification of above classes
template<class Elem>
BinAVLTreeNode<Elem>::BinAVLTreeNode() :
	balanceFactor(EAQUAL_HIGH), lChild(nullptr), rChild(nullptr) {};
template<class Elem>
BinAVLTreeNode<Elem>::BinAVLTreeNode(const Elem &elem, int m_bf,
	BinAVLTreeNode<Elem> *m_lChild, BinAVLTreeNode<Elem> *m_rChild) :
	data(elem), balanceFactor(m_bf), lChild(m_lChild), rChild(m_rChild) {};
template<class Elem>
BinAVLTreeNode<Elem>::BinAVLTreeNode(const BinAVLTreeNode<Elem>& copy) {
	data = copy.data;
	balanceFactor = copy.balanceFactor;
	lChild = copy.lChild;
	rChild = copy.rChild;
}
template<class Elem>
BinAVLTreeNode<Elem>* operator=(const BinAVLTreeNode<Elem>& copy) {
	if (&copy != this) {
		data = copy.data;
		balanceFactor = coppy.balanceFactor;
		lChild = copy.lChild;
		rChild = copy.rChild;
	}
	return *this;
}
template<class Elem>
BinAVLTreeNode<Elem>::~BinAVLTreeNode() {
	delete lChild;
	lChild = nullptr;
	delete rChild;
	rChild = nullptr;
}
#endif // !_BINAVLTREE_H_

