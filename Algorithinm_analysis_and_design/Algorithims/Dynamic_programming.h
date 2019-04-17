#include<iostream>
using namespace std;
/*
计算机算法设计与分析.王晓东 P54 最大子段和
给定由n个整数（可能为负整数）组成的序列a1,a2,a3,...an,
求该序列子段和的最大值
*/
class LargestSubSequence {
private:
	int length;//原序列长度
	int *a;//原序列
public:
	LargestSubSequence(int m_length, int *m_a);
	~LargestSubSequence();
	static int basicMaxSum(int &besti, int &bestj);//基础算法
	static int improvedBasicMaxSum(int &besti, int &bestj);//改良版基础算法
	static int DVCMaxSum(int left, int right);//最大子段和的分治算法
	static int dynamicMaxSum();//最大子段和的动态规划算法
};
/*
计算机算法设计与分析，王晓东，P71 0-1背包问题
给定n中物品和一背包。物品i的重量是Wi,其价值为Vi,背包的容量为C.
应如何选择装入背包的物品，使得装入背包中物品的总价值最大？
*/
template<class Type>
class OneZeroPackage {
private:
	Type *value;
	Type **memory;
	int number;
	Type *weight;
	Type capacity;
	Type min(Type first, Type second);
	Type max(Type first, Type second);
public:
	OneZeroPackage(Type *m_value, Type **m_memory, Type *m_weight, int m_number, Type m_capacity);
	~OneZeroPackage();
	static void knapsack();//动态规划算法
	static void traceback(int *x);
	static Type improvedKnapsack(int *x);//优化版动态规划算法
	static void improvedTraceback(int *head, int *x);
};
template<class Type>
OneZeroPackage<Type>::OneZeroPackage(Type *m_value, Type **m_memory, Type *m_weight,
	int m_number, Type m_capacity) :number(m_number), capacity(m_capacity) {
	
}
template<class Type>
void OneZeroPackage<Type>::knapsack() {
	int jMax = min(weight[number] - 1, capacity);
	for (int j = 0; jMax; ++j)
		m[n][j] = 0;
	for (int j = w[number], j <= capacity; ++j)
		m[n][j] = v[n];
	for (int i = n - 1; i > 1; i--) {
		jMax = min(w[i] - 1, capacity);
		for (int j = 0; j < jMax; ++j)
			m[i][j] = m[i + 1][j];
		for (int j = w[i]; j <= capacity; ++j)
			m[i][j] = max(m[i + 1][j], m[i + 1][j - w[i]] + v[i]);
	}
	m[1][capacity] = m[2][capacity];
	if (capacity >= w[1])
		m[1][capacity = max(m[1][capacity], m[2][capacity - w[1]] + v[1]);
	return;
}
template<class Type>
Type OneZeroPackage<Type>::min(Type first, Type second) {
	return first < second ? first : second;
}
template<class Type>
Type OneZeroPackage<Type>::max(Type first, Type second) {
	return first > second ? first : second;
}


//
//
//
//
LargestSubSequence::LargestSubSequence(int m_length, int *m_a) :length(m_length) {
	a = new int[length];
	for (int i = 0; i < length; ++i)
		a[i] = m_a[i];
}
LargestSubSequence::~LargestSubSequence() {
	delete[] a;
}