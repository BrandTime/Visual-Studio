#include<iostream>
using namespace std;
/*
������㷨��������.������ P54 ����Ӷκ�
������n������������Ϊ����������ɵ�����a1,a2,a3,...an,
��������Ӷκ͵����ֵ
*/
class LargestSubSequence {
private:
	int length;//ԭ���г���
	int *a;//ԭ����
public:
	LargestSubSequence(int m_length, int *m_a);
	~LargestSubSequence();
	static int basicMaxSum(int &besti, int &bestj);//�����㷨
	static int improvedBasicMaxSum(int &besti, int &bestj);//����������㷨
	static int DVCMaxSum(int left, int right);//����Ӷκ͵ķ����㷨
	static int dynamicMaxSum();//����Ӷκ͵Ķ�̬�滮�㷨
};
/*
������㷨������������������P71 0-1��������
����n����Ʒ��һ��������Ʒi��������Wi,���ֵΪVi,����������ΪC.
Ӧ���ѡ��װ�뱳������Ʒ��ʹ��װ�뱳������Ʒ���ܼ�ֵ���
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
	static void knapsack();//��̬�滮�㷨
	static void traceback(int *x);
	static Type improvedKnapsack(int *x);//�Ż��涯̬�滮�㷨
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