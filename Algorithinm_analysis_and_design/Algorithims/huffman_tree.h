#ifndef _HUFFMAN_TREE_
#define _HUFFMAN_TREE_
#include"lk_queue.h"
#include"lk_stack.h"
#include<string>
#include<vector>

string VecToString(vector<char> &ivec) {
	string temp("");
	for (auto i : ivec)
		temp.push_back(i);
	return temp;
}
template<class WeightType>
struct HuffmanTreeNode {
	WeightType weight;
	unsigned int parent, lChild, rChild;

	HuffmanTreeNode() :parent(0), lChild(0), rChild(0) {};
	HuffmanTreeNode(WeightType w, int p = 0, int leftchild = 0,
		int rightchild = 0) {
		weight = w;
		parent = p;
		lChild = leftchild;
		rChild = rightchild;
	}
};
template<class CharType,class WeightType>
class HuffmanTree {
protected:
	HuffmanTreeNode<WeightType> *nodes;//存储结点信息，nodes[0]未用
	CharType *LeafChars;//存储结点字符信息，LeafChaars[0]未用
	string *LeafCodes;//存储叶节点字符编码信息,LeafCodes[0]未用
	unsigned int curPos,total;//译码时从根节点到叶节点路径的当前结点
	unsigned int num;//存储叶节点个数

	void Select(unsigned int cur, unsigned int &r1, unsigned int &r2);
	//从nodes[1~cur]中选择双亲为0，权值最小的两个结点
	void CreatHuffmanTree(CharType ch[], WeightType w[], unsigned int n);
	//由字符，权值和字符个数构造哈夫曼树
	void DestroyHelp();
	void DisplayHelp(unsigned int r,
		int level,void (*visit)(WeightType &));
public:
	HuffmanTree(CharType ch[], WeightType w[], unsigned int n);
	HuffmanTree(const HuffmanTree<CharType, WeightType> &copy);
	HuffmanTree<CharType,WeightType>& operator=(
		const HuffmanTree<CharType,WeightType> &copy);
	virtual ~HuffmanTree();
	string Encode(CharType ch);
	vector<CharType> Decode(const string &strCode);
	void Display(void (*visit)(WeightType &));
};
template<class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::DisplayHelp(unsigned int r,
	int level,void (*visit)(WeightType &)) {
	if (r==0)
		return;
	else {
		DisplayHelp(nodes[r].rChild,level+1,visit);
		for (int i = 0; i < level; ++i)
			cout << "  ";
		(*visit)(nodes[r].weight);
		cout << endl;
		DisplayHelp(nodes[r].lChild,level+1,visit);
		return;
	}
}
template<class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::Display(void(*visit)(WeightType &)) {
	unsigned int i = 1;
	for (; i <= num*2-1; ++i)
		if (nodes[i].parent == 0)
			break;
	if (i)
		DisplayHelp(i, 0, visit);
	else
		throw runtime_error("ERROR");
	return;
}
template<class CharType, class WeightType>
HuffmanTree<CharType, WeightType>& HuffmanTree<CharType, WeightType>::operator=(
	const HuffmanTree<CharType, WeightType> &copy) {
	if (&copy != this) {
		if (num)
			DestroyHelp();
		unsigned int m = copy.num * 2 - 1, pos = 0;
		nodes = new HuffmanTreeNode<WeightType>[m + 1];
		LeafChars = new CharType[copy.num + 1];
		LeafCodes = new string[copy.num + 1];
		curPos = copy.curPos;
		num = copy.num;
		for (pos = 1; pos < m + 1; ++pos)
			nodes[pos] = copy.nodes[pos];
		for (pos = 1; pos < num + 1; ++pos)
			LeafChars[pos] = copy.LeafChars[pos];
		for (pos = 1; pod < num + 1; ++pos)
			LeafCodes[pos] = copy.LeafCodes[pos];
	}
	return *this;
}
template<class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(const HuffmanTree<CharType, WeightType> &copy) {
	if (num != 0)
		DestroyHelp();
	unsigned int m = copy.num * 2 - 1,pos=0;
	nodes = new HuffmanTreeNode<WeightType>[m+1];
	LeafChars = new CharType[copy.num+1];
	LeafCodes = new string[copy.num+1];
	curPos = copy.curPos;
	num = copy.num;
	for (pos = 1; pos < m + 1; ++pos)
		nodes[pos] = copy.nodes[pos];
	for (pos = 1; pos < num + 1; ++pos)
		LeafChars[pos] = copy.LeafChars[pos];
	for (pos = 1; pos < num + 1; ++pos)
		LeafCodes[pos] = copy.LeafCodes[pos];
}
template<class CharType, class WeightType>
vector<CharType> HuffmanTree<CharType, WeightType>::Decode(const string &strCode) {
	vector<CharType> ivec;
	for (auto iter = strCode.cbegin(); iter != strCode.cend(); ++iter) {
		if (*iter == '0') 
			curPos = nodes[curPos].lChild;
		else
			curPos = nodes[curPos].rChild;
		if (nodes[curPos].lChild == 0 && nodes[curPos].rChild == 0) {
			ivec.push_back(LeafChars[curPos]);
			curPos = num*2-1;
		}
	}
	return ivec;
}
template<class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::DestroyHelp() {
	delete[] nodes;
	delete[] LeafChars;
	delete[] LeafCodes;
	num = 0;
	curPos = 0;
	return;
}
template<class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::~HuffmanTree() {
	DestroyHelp();
}
template<class CharType, class WeightType>
string HuffmanTree<CharType, WeightType>::Encode(CharType ch) {
	for (unsigned int i = 1; i <= num; ++i)
		if (LeafChars[i] == ch)
			return LeafCodes[i];
	return "nullptr";
}
template<class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::Select(unsigned int cur,
	unsigned int &r1, unsigned int &r2) {
	if (cur<=2)
		throw runtime_error("the interval is not correct");
	for (unsigned int i = 1; i <= cur; ++i) {
		if (nodes[i].parent == 0) {
			if (r1&&r2) {
				if (nodes[i].weight < nodes[r1].weight) {
					r2 = r1;
					r1 = i;
				}
				else if (nodes[i].weight >= nodes[r1].weight&&
					nodes[i].weight <= nodes[r2].weight) {
					r2 = i;
				}
			}
			else {
				if(!r1)
					r1 = i;
				if (i != r1)
					r2 = i;
			}
		}
	}
	return;
}
template<class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::CreatHuffmanTree(CharType ch[],
	WeightType w[], unsigned int n) {
	num = n;
	unsigned int m = n * 2 - 1;
	
	nodes = new HuffmanTreeNode<WeightType>[m + 1];
	LeafChars = new CharType[n + 1];
	LeafCodes = new string[n + 1];
	unsigned int pos = 0;
	for (pos = 1; pos <= n; ++pos) {
		nodes[pos].weight = w[pos - 1];
		LeafChars[pos] = ch[pos - 1];
	}
	for (pos = n+1; pos < m + 1; ++pos) {
		unsigned int r1=0, r2=0;
		Select(pos-1, r1, r2);	
		nodes[pos].weight = nodes[r1].weight + nodes[r2].weight;
		nodes[r1].parent = nodes[r2].parent = pos;
		nodes[pos].lChild = r1;
		nodes[pos].rChild = r2;
	}
	for (pos = 1; pos <= n; ++pos) {
		auto cur = pos;
		unsigned int m_parent = nodes[cur].parent;
		vector<char> temp;
		while (m_parent != 0) {
			if (nodes[m_parent].lChild == cur)
				temp.insert(temp.begin(),'0');
			else if (nodes[m_parent].rChild == cur)
				temp.insert(temp.begin(),'1');
			else
				throw runtime_error("the tree structure is wrong");
			cur = m_parent;
			m_parent = nodes[m_parent].parent;
		}
		LeafCodes[pos]= VecToString(temp);
		temp.clear();
	}
	curPos = m;
	return;
}
template<class CharType, class WeightType>
HuffmanTree<CharType,WeightType>::HuffmanTree(
	CharType ch[], WeightType w[], unsigned int n) {
	CreatHuffmanTree(ch, w, n);
}



//debug program
#if 0
#include"huffman_tree.h"

template<class WeightType>
void Visit(WeightType &w) {
	cout << w;
	return;
}
int main(void) {
	try {
		char ch[] = { 'F','O','R','G','E','T' };
		int w[] = { 2,3,4,4,5,7 };
		int n = 6;

		HuffmanTree<char, int> huffmantree(ch, w, n);
		HuffmanTree<char, int> huffmantree1(huffmantree);
		string strText = "FORGET";
		string strCode = "0100111101110010";
		huffmantree.Display(&Visit);
		cout << "------------------------------------" << endl;
		huffmantree1.Display(&Visit);
		cout << "------------------------------------" << endl;
		cout << "文本串" << strText << "的编码为：" << endl;
		for (auto i : strText)
			cout << huffmantree.Encode(i);
		cout << endl;
		system("PAUSE");
		vector<char> ivec = huffmantree.Decode(strCode);
		cout << "编码" << strCode << "的文本串为：" << endl
			<< VecToString(ivec);
		cout << endl;
	}
	catch (runtime_error &err) {
		cout << err.what() << endl;
	}

	system("PAUSE");
	return 0;
}
#endif
#endif // !_HUFFMAN_TREE_
