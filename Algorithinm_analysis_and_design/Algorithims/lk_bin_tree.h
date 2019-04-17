#ifndef _LK_BINARY_TREE_
#define _LK_BINARY_TREE_
#include"lk_stack.h"
#include"lk_queue.h"
template<class Elem>
struct BinTreeNode {
	Elem data;
	BinTreeNode<Elem> *lChild;
	BinTreeNode<Elem> *rChild;

	BinTreeNode() :lChild(nullptr), rChild(nullptr) {};
	BinTreeNode(const Elem &elem,
		BinTreeNode<Elem> *leftchild = nullptr,
		BinTreeNode<Elem> *rightchild = nullptr);
};

template<class Elem>
class LkBinTree {
protected:
	BinTreeNode<Elem> *root;
	BinTreeNode<Elem>* CopyTreeHelp(const BinTreeNode<Elem> *r);
	//������rΪ���Ķ������������µĶ������ĸ�
	void DestroyHelp(BinTreeNode<Elem> *r);
	//������rΪ���Ķ�����
	void PreOrderHelp(BinTreeNode<Elem> *r, void(*visit)(Elem &));
	//�������
	void InOrderHelp(BinTreeNode<Elem> *r, void(*visit)(Elem &));
	//�������
	void PostOrderHelp(BinTreeNode<Elem> *r, void(*visit)(Elem &));
	//�������
	int HeightHelp(const BinTreeNode<Elem> *r) const;
	//���ض������ĸ�
	int NodeCountHelp(const BinTreeNode<Elem> *r) const;
	//���ض������ڵ�ĸ���
	BinTreeNode<Elem>* ParentHelp(BinTreeNode<Elem> *r,
		BinTreeNode<Elem> *pattern)const;
	//���ؽڵ��˫��
public:
	LkBinTree();
	LkBinTree(BinTreeNode<Elem> *r);
	//������rΪ���Ķ�����
	LkBinTree(const LkBinTree<Elem> &copy);
	LkBinTree<Elem>& operator=(const LkBinTree<Elem> &copy);
	virtual ~LkBinTree();
	BinTreeNode<Elem>* GetRoot()const;
	//���ض������ĸ�
	bool Empty()const;
	int NodeCount()const;
	int GetHeight()const;
	void GetElem(BinTreeNode<Elem> *cur, Elem &elem);
	//���ص�ǰ�ڵ��ֵ
	void SetElem(BinTreeNode<Elem> *cur, Elem &elem);
	//Ϊ��ǰ�ڵ㸳ֵ
	void PreOrder(void(*visit)(Elem &));
	void InOrder(void(*visit)(Elem &));
	void PostOrder(void(*visit)(Elem &));
	BinTreeNode<Elem>* LeftChild(const BinTreeNode<Elem> *cur)const;
	//����cur�ڵ������
	BinTreeNode<Elem>* RightChild(const BinTreeNode<Elem> *cur)const;
	//�����Һ���
	BinTreeNode<Elem>* Parent(BinTreeNode<Elem> *pattern)const;
	//����˫��
	void InsertLeftChild(BinTreeNode<Elem> *cur, const Elem &elem);
	//��������
	void InsertRightChild(BinTreeNode<Elem> *cur, const Elem &elem);
	void RemoveLeftChild(BinTreeNode<Elem> *cur);
	void RemoveRightChild(BinTreeNode<Elem> *cur);
};
template<class Elem>
void NonRecurPreOrder(const LkBinTree<Elem> &bt, void(*visit)(Elem &));
//�ǵݹ��������������
template<class Elem>
void NonRecurInOrder(const LkBinTree<Elem> &bt, void(*visit)(Elem &));
//�ǵݹ��������������
template<class Elem>
BinTreeNode<Elem>* GoFarLeft(BinTreeNode<Elem> *r, Stack<BinTreeNode<Elem>*> &s);
//�ǵݹ����������������������ĳ�����������
template<class Elem>
void NonRecurPostOrder(const LkBinTree<Elem> &bt, void(*visit)(Elem &));
//�ǵݹ��������������
template<class Elem>
pair<BinTreeNode<Elem>*, bool>* GoFarLeft(BinTreeNode<Elem> *r,
	Stack<pair<BinTreeNode<Elem>*, bool>*> &s);
//�ǵݹ���������������������������ĳ�ڵ��������㣨pair�е�boolֵ��ʾ��ǰ�����������Ƿ��ѱ������true
//�����ѱ������false��ʾδ�����
template<class Elem>
void DisplayBTWithTreeShapeHelp(BinTreeNode<Elem> *r, int level);
//����״��ʽ��ʾ��rΪ���Ķ�������levelΪ�������������ڵ�Ĳ����Ϊ1
template<class Elem>
void DisplayBTWithTreeShape(LkBinTree<Elem> &bt);
//��״��ʽ��ʾ������
template<class Elem>
void CreatBinaryTreeHelp(BinTreeNode<Elem>* &r, Elem pre[], Elem in[], int
	preLeft, int preRight, int inLeft, int inRight);
//��֪��������ǰ������pre[preLeft,preRight]����������in[inLeft,inRight]
//������rΪ���Ķ�����
template<class Elem>
LkBinTree<Elem> CreatBinaryTree(Elem pre[], Elem in[], int n);
//��֪ǰ����������й��������
//
//
//
//
//
//
//
//the specificaton of above global functions
template<class Elem>
void NonRecurPreOrder(const LkBinTree<Elem> &bt, void(*visit)(Elem &)) {
	Stack<BinTreeNode<Elem> *> node;
	BinTreeNode<Elem> *cur = bt.GetRoot();

	while (cur) {
		(*visit)(cur->data);
		node.Push(cur);
		if (cur->lChild != nullptr)
			cur = cur->lChild;
		else {
			if (cur->rChild != nullptr)
				cur = cur->rChild;
			else {
				while (!node.Empty()) {
					node.Pop(cur);
					cur = cur->rChild;
					if (cur)
						break;
				}
			}
		}
	}
	return;
}
template<class Elem>
void NonRecurInOrder(const LkBinTree<Elem> &bt, void(*visit)(Elem &)) {
	BinTreeNode<Elem> *cur = bt.GetRoot();
	Stack<BinTreeNode<Elem>*> node;
	cur = GoFarLeft(cur, node);
	while (cur) {
		(*visit)(cur->data);
		if (cur->rChild) {
			cur = cur->rChild;
			cur = GoFarLeft(cur, node);
		}
		else if (!node.Empty())
			node.Pop(cur);
		else
			cur = nullptr;
	}
	return;
}
template<class Elem>
BinTreeNode<Elem>* GoFarLeft(BinTreeNode<Elem> *r, Stack<BinTreeNode<Elem>*> &s) {
	if (r == nullptr)
		return nullptr;
	else {
		BinTreeNode<Elem> *next = r;
		while (next->lChild!=nullptr) {
			s.Push(next);
			next = next->lChild;
		}
		return next;
	}
}
template<class Elem>
pair<BinTreeNode<Elem>*, bool>* GoFarLeft(BinTreeNode<Elem> *r,
	Stack<pair<BinTreeNode<Elem>*, bool>*> &s) {
	if (r == nullptr)
		return nullptr;
	else {
		pair<BinTreeNode<Elem>*, bool> *next = new pair<BinTreeNode<Elem>*, bool>(r, false);;
		while (next->first->lChild) {
			s.Push(next);
			next = new pair<BinTreeNode<Elem>*, bool>(next->first->lChild, false);
		}
		return next;
	}
}
template<class Elem>
void NonRecurPostOrder(const LkBinTree<Elem> &bt, void(*visit)(Elem &)) {
	Stack<pair<BinTreeNode<Elem>*, bool>*> node;
	pair<BinTreeNode<Elem>*, bool> *cur = GoFarLeft(bt.GetRoot(), node);
#if 0
	//myown version
	while (cur) {
		(*visit)(cur->first->data);
		if (cur->second) {
			delete cur;
			cur = nullptr;
		}
		if (!node.Empty()) {
			node.Pop(cur);
		}
		if (cur&&cur->second == false && cur->first->rChild) {
			cur->second = true;
			node.Push(cur);
			cur = GoFarLeft(cur->first->rChild, node);
		}
	}
#endif;
	//textbook version,���ݽṹ���㷨 C++�����Ű�p205
	while (cur) {
		if (cur->first->rChild == nullptr || cur->second) {
			//��ǰ���������Ϊ�ջ��������ѱ�����
			(*visit)(cur->first->data);
			delete cur;
			cur = nullptr;
			if (!node.Empty())
				node.Pop(cur);
		}
		else {
			//��ǰ���������δ������
			cur->second = true;
			node.Push(cur);
			cur = GoFarLeft(cur->first->rChild, node);
		}
	}
	return;
}
template<class Elem>
void DisplayBTWithTreeShapeHelp(BinTreeNode<Elem> *r, int level) {
	if (!r)
		return;
	DisplayBTWithTreeShapeHelp(r->rChild, level + 1);
	for (int i = 0; i < level; ++i)
		cout << "  ";
	cout << r->data << endl;
	DisplayBTWithTreeShapeHelp(r->lChild, level + 1);
	return;
}
template<class Elem>
void DisplayBTWithTreeShape(LkBinTree<Elem> &bt) {
	DisplayBTWithTreeShapeHelp(bt.GetRoot(), 0);
	return;
}
template<class Elem>
void CreatBinaryTreeHelp(BinTreeNode<Elem>* &r, Elem pre[], Elem in[], int
	preLeft, int preRight, int inLeft, int inRight) {
	if (inLeft > inRight)
		r = nullptr;
	else {
		r = new BinTreeNode<Elem>(pre[preLeft]);
		int mid = inLeft;
		while (in[mid] != pre[preLeft])
			++mid;
		CreatBinaryTreeHelp(r->lChild, pre, in, preLeft + 1, preLeft + mid - inLeft, inLeft, mid - 1);
		CreatBinaryTreeHelp(r->rChild, pre, in, preLeft + 1 + mid - inLeft, preRight, mid + 1, inRight);
	}
	return;
}
template<class Elem>
LkBinTree<Elem> CreatBinaryTree(Elem pre[], Elem in[], int n) {
	BinTreeNode<Elem> *r = nullptr;
	CreatBinaryTreeHelp(r, pre, in, 0, n - 1, 0, n - 1);
	LkBinTree<Elem> temp(r);
	return temp;
}
//
//the specification of above classes
//second class:
template<class Elem>
void LkBinTree<Elem>::RemoveRightChild(BinTreeNode<Elem> *cur) {
	DestroyHelp(cur->rChild);
	cur->rChild = nullptr;
	return;
}
template<class Elem>
void LkBinTree<Elem>::RemoveLeftChild(BinTreeNode<Elem> *cur) {
	DestroyHelp(cur->lChild);
	cur->lChild = nullptr;
	return;
}
template<class Elem>
void LkBinTree<Elem>::InsertRightChild(BinTreeNode<Elem> *cur, const Elem &elem) {
	if (cur->rChild)
		throw runtime_error("Error");
	cur->rChild = new BinTreeNode<Elem>(elem);
	return;
}
template<class Elem>
void LkBinTree<Elem>::InsertLeftChild(BinTreeNode<Elem> *cur, const Elem &elem) {
	if (cur->lChild)
		throw runtime_error("Error");
	cur->lChild = new BinTreeNode<Elem>(elem);
	return;
}
template<class Elem>
BinTreeNode<Elem>* LkBinTree<Elem>::Parent(BinTreeNode<Elem> *pattern)const {
	if (!pattern)
		throw runtime_error("this node doesn't exist");
	return ParentHelp(root, pattern);
}
template<class Elem>
BinTreeNode<Elem>* LkBinTree<Elem>::RightChild(const BinTreeNode<Elem> *cur)const {
	if (!cur)
		throw runtime_error("this node doesn't exist");
	return cur->rChild;
}
template<class Elem>
BinTreeNode<Elem>* LkBinTree<Elem>::LeftChild(const BinTreeNode<Elem> *cur)const {
	if (!cur)
		throw runtime_error("this node doesn't exist");
	return cur->lChild;
}
template<class Elem>
void LkBinTree<Elem>::InOrderHelp(BinTreeNode<Elem> *r, void(*visit)(Elem &)) {
	if (r == nullptr)
		return;
	else {
		InOrderHelp(r->lChild, visit);
		(*visit)(r->data);
		InOrderHelp(r->rChild, visit);
	}
	return;
}
template<class Elem>
void LkBinTree<Elem>::PreOrderHelp(BinTreeNode<Elem> *r, void(*visit)(Elem &)) {
	if (r == nullptr)
		return;
	else {
		(*visit)(r->data);
		PreOrderHelp(r->lChild, visit);
		PreOrderHelp(r->rChild, visit);
	}
	return;
}
template<class Elem>
void LkBinTree<Elem>::PostOrderHelp(BinTreeNode<Elem> *r, void(*visit)(Elem &)) {
	if (r == nullptr)
		return;
	else {
		PostOrderHelp(r->lChild, visit);
		PostOrderHelp(r->rChild, visit);
		(*visit)(r->data);
	}
	return;
}
template<class Elem>
void LkBinTree<Elem>::PostOrder(void(*visit)(Elem &)) {
	if (!root)
		throw runtime_error("the tree doesn't exist");
	PostOrderHelp(root, visit);
	return;
}
template<class Elem>
void LkBinTree<Elem>::InOrder(void(*visit)(Elem &)) {
	if (!root)
		throw runtime_error("the tree doesn't exist");
	InOrderHelp(root, visit);
	return;
}
template<class Elem>
void LkBinTree<Elem>::PreOrder(void(*visit)(Elem &)) {
	if (!root)
		throw runtime_error("the tree dosen't exist");
	PreOrderHelp(root, visit);
	return;
}
template<class Elem>
void LkBinTree<Elem>::SetElem(BinTreeNode<Elem> *cur, Elem &elem) {
	if (!cur)
		throw runtime_error("Error");
	cur->data = elem;
	return;
}
template<class Elem>
void LkBinTree<Elem>::GetElem(BinTreeNode<Elem> *cur, Elem &elem) {
	if (!cur)
		throw runtime_error("Error");
	elem = cur->data;
	return;
}
template<class Elem>
int LkBinTree<Elem>::GetHeight()const {
	return HeightHelp(root);
}
template<class Elem>
int LkBinTree<Elem>::NodeCount() const {
	return NodeCountHelp(root);
}
template<class Elem>
bool LkBinTree<Elem>::Empty()const {
	return root == nullptr;
}
template<class Elem>
BinTreeNode<Elem>* LkBinTree<Elem>::GetRoot()const {
	return root;
}
template<class Elem>
LkBinTree<Elem>::~LkBinTree() {
	DestroyHelp(root);
}
template<class Elem>
LkBinTree<Elem>& LkBinTree<Elem>::operator=(const LkBinTree<Elem> &copy) {
	if (&copy != this) {
		if (root)
			DestroyHelp(root);
		root = CopyTreeHelp(copy.root);
	}
	return *this;
}
template<class Elem>
BinTreeNode<Elem>* LkBinTree<Elem>::ParentHelp(BinTreeNode<Elem> *r,
	BinTreeNode<Elem> *pattern)const {
	if (!r)
		throw runtime_error("the tree dosen't exist, cannot get parent");
	Lk_queue<BinTreeNode<Elem>*> queue;
	queue.In_queue(r);
	while (!queue.Empty()) {
		BinTreeNode<Elem> *cur, *leftchild, *rightchild;
		queue.Out_queue(cur);
		leftchild = cur->lChild;
		rightchild = cur->rChild;
		if ((leftchild&&leftchild->data == pattern->data) ||
			(rightchild&&rightchild->data == pattern->data))
			return cur;
		queue.In_queue(leftchild);
		queue.In_queue(rightchild);
	}
	return nullptr;
}
template<class Elem>
int LkBinTree<Elem>::NodeCountHelp(const BinTreeNode<Elem> *r)const {
	if (r == nullptr)
		return 0;
	else
		return NodeCountHelp(r->lChild) + NodeCountHelp(r->rChild) + 1;
}
template<class Elem>
int LkBinTree<Elem>::HeightHelp(const BinTreeNode<Elem> *r) const {
	if (r == nullptr)
		return 0;
	else {
		int left = HeightHelp(r->lChild), right = HeightHelp(r->rChild);
		return (left > right ? left : right) + 1;
	}
}
template<class Elem>
void LkBinTree<Elem>::DestroyHelp(BinTreeNode<Elem> *r) {
	if (r) {
		DestroyHelp(r->lChild);
		DestroyHelp(r->rChild);
		r->rChild = nullptr;
		r->lChild = nullptr;
		delete r;
		r = nullptr;
	}
	return;
}
template<class Elem>
LkBinTree<Elem>::LkBinTree(BinTreeNode<Elem> *r) {
	if (root)
		DestroyHelp(root);
	root = CopyTreeHelp(r);
}
template<class Elem>
LkBinTree<Elem>::LkBinTree(const LkBinTree& copy) {
	root = CopyTreeHelp(copy.GetRoot());
}
template<class Elem>
LkBinTree<Elem>::LkBinTree() :root(nullptr) {};
template<class Elem>
BinTreeNode<Elem>* LkBinTree<Elem>::CopyTreeHelp(const BinTreeNode<Elem> *r) {
	if (r == nullptr)
		return nullptr;
	else {
		BinTreeNode<Elem> *lChild = CopyTreeHelp(r->lChild);
		BinTreeNode<Elem> *rChild = CopyTreeHelp(r->rChild);
		BinTreeNode<Elem> *rt = new BinTreeNode<Elem>(r->data, lChild, rChild);
		return rt;
	}
}
//first class:
template<class Elem>
BinTreeNode<Elem>::BinTreeNode(const Elem &elem,
	BinTreeNode<Elem> *leftchild,BinTreeNode<Elem> *rightchild) {
	data = elem;
	lChild = leftchild;
	rChild = rightchild;
}
//
//
//debug program
#if 0
#include"lk_binary_tree.h"

template<class Elem>
void Print(Elem temp[], int n) {
	for (int i = 0; i < n; ++i)
		cout << temp[i] << "\t";
	cout << endl;
	return;
}
void Divideline() {
	cout << endl << "------------------------" << endl;
	return;
}
template<class Elem>
void visit(Elem &elem) {
	cout << elem << endl;
	return;
}
int main(void) {
	try {
		char *PRE1 = "ABCDEFGHI", *IN1 = "DCBAGFHEI",
			*PRE2 = "ABCDEFGHIJ", *IN2 = "CBEDAGHFJI";
		LkBinTree<char> bintree = CreatBinaryTree(PRE1, IN1, 9),
			bintree0(CreatBinaryTree(PRE2, IN2, 10));
		LkBinTree<char> bintree1(bintree0.GetRoot()), bintree2;
		bintree0 = bintree2 = bintree;
		DisplayBTWithTreeShape(bintree);
		Divideline();
		DisplayBTWithTreeShape(bintree1);
		Divideline();
		DisplayBTWithTreeShape(bintree0);
		Divideline();
		cout << "the total node of bintree:\t" << bintree.NodeCount() << endl;
		cout << "the height of bintree:\t" << bintree.GetHeight() << endl;
		char temp = 'X';
		bintree.SetElem(bintree.GetRoot(), temp);
		temp = 'M';
		bintree.GetElem(bintree.GetRoot(), temp);
		cout << "return the value of current node:\t" << temp << endl;
		cout << "print all nodes in PREORDER:\t";
		bintree.PreOrder(visit);
		Divideline();
		cout << "print all nodes in INORDER:\t";
		bintree.InOrder(visit);
		Divideline();
		cout << "print all nodes in POSTORDER:\t";
		bintree.PostOrder(visit);
		Divideline();
		BinTreeNode<char> *tempnode = bintree.GetRoot();
		while (tempnode->lChild || tempnode->rChild)
			tempnode = tempnode->rChild;
		bintree.InsertLeftChild(tempnode, 'U');
		bintree.InsertRightChild(tempnode, 'V');
		DisplayBTWithTreeShape(bintree);
		Divideline();
		bintree.RemoveLeftChild(tempnode);
		bintree.RemoveRightChild(tempnode);
		DisplayBTWithTreeShape(bintree);
		Divideline();
		tempnode = bintree.Parent(tempnode);
		cout << "the parent node of current node:\t" << tempnode->data << endl;
	}
	catch (runtime_error& err) {
		cout << err.what() << endl;
	}

	system("PAUSE");
	return 0;
}
#endif
#endif
