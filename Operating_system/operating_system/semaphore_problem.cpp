#if 0
/*题目3：
一个从键盘输入到打印机输出的数据处理流程如图所示。
其中键盘输入进程通过缓冲区buf1把数据传送给计算进程，
计算进程把处理结果通过buf2传送给打印进程。
假设上述两个缓冲区的大小分别为n1和n2，
请用PV信号量实现键盘输入进程，计算进程及打印进程间的同步算法。

Input->buf1->Caculate->buf2->Print_out
*/
#include<windows.h>
#include<iostream>
#include<fstream>
using namespace std;

inline void sleep(unsigned long n) {
	Sleep(1000 * n);
	return;
}
struct ThreadInfo {
	int tid;
	char role;//C reresents calculator,
	//P represents print out and I represents Input
	double delay;
	double persist;
};
HANDLE buf_1_sema, buf_2_sema;
HANDLE buf_1_operate_sema, buf_2_operate_sema;
HANDLE input_caculate_sema, caculate_print_sema;
const int TOTALTHREAD = 100;
const int N1 = 2, N2 = 2;
int n1 = 0, n2 = 0;
void inputThread(void *p);
void caculateThread(void *p);
void printThread(void *p);
void printBufferState();

int main(void) {
	DWORD thread_count = 0;
	DWORD thread_ID;
	ThreadInfo thread_info[TOTALTHREAD];
	HANDLE thread[TOTALTHREAD];
	buf_1_sema = CreateSemaphore(nullptr, 0, N1, (LPCSTR)"semaphore_for_buf_1");
	buf_2_sema = CreateSemaphore(nullptr, 0, N2, (LPCSTR)"semaphore_for_buf_2");
	buf_1_operate_sema = CreateSemaphore(nullptr, 1,1, (LPCSTR)"semaphore_for_buf_1_operation");
	buf_2_operate_sema = CreateSemaphore(nullptr, 1,1, (LPCSTR)"semaphore_for_buf_2_operation");
	fstream infile;
	infile.open("test.txt");
	if (!infile) {
		printf("Error in open file\n");
		cin.get();
		return -1;
	}
	while (!infile.eof()) {
		infile >> thread_info[thread_count].tid;
		infile >> thread_info[thread_count].role;
		infile >> thread_info[thread_count].delay;
		infile >> thread_info[thread_count].persist;
		thread_count++;
	}
	for (int i = 0; i < thread_count; ++i) {
		if (thread_info[i].role == 'I' || thread_info[i].role == 'i')
			thread[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(inputThread),
				&thread_info[i], 0, &thread_ID);
		else if (thread_info[i].role == 'C' || thread_info[i].role == 'c')
			thread[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(caculateThread),
				&thread_info[i], 0, &thread_ID);
		else
			thread[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(printThread),
				&thread_info[i], 0, &thread_ID);
	}
	WaitForMultipleObjects(thread_count,thread,true,-1);
	printf("All input, caculate and print threads have finished operating\n");

	cin.get();
	return 0;
}
void printBufferState() {
	printf("Current volume of buffer 1 is: %d\n", n1);
	printf("Current volume of buffer 2 is: %d\n\n", n2);
	return;
}
void printThread(void *p) {
	DWORD m_delay = ((ThreadInfo *)p)->delay;
	DWORD m_persist = ((ThreadInfo *)p)->persist;
	DWORD m_id = ((ThreadInfo *)p)->tid;
	printf("Print thread %d sends print request to buffer_2\n", m_id);
	sleep(m_delay);
	WaitForSingleObject(buf_2_sema, -1);
	printf("Print thread %d begins printing\n", m_id);
	sleep(m_persist);
	printf("Print thread %d finishes printing\n\n", m_id);
	n2--;
	printBufferState();
	ReleaseSemaphore(buf_1_operate_sema,1,nullptr);
	return;
}
void caculateThread(void *p) {
	DWORD m_delay = ((ThreadInfo *)p)->delay;
	DWORD m_persist = ((ThreadInfo *)p)->persist;
	DWORD m_id = ((ThreadInfo *)p)->tid;
	printf("Caculate Thread %d sends caculate request to buffer_1 and"
		" write request to buffer_2\n", m_id);
	sleep(m_delay);
	while (n2 == N2)
		WaitForSingleObject(buf_2_operate_sema, -1);
	WaitForSingleObject(buf_1_sema, -1);
	printf("Caculate thread %d begins caculating\n", m_id);
	sleep(m_persist);
	printf("Caculate thread %d finishes caculating\n", m_id);
	n1--;
	printf("Caculate thread %d begins writing to buffer_2\n", m_id);
	sleep(m_persist);
	printf("Caculate thread %d finishes writing to buffer_2\n\n", m_id);
	n2++;
	printBufferState();
	ReleaseSemaphore(buf_2_sema, 1, nullptr);
	ReleaseSemaphore(buf_1_operate_sema,1,nullptr);
	return;
}
void inputThread(void *p) {
	DWORD m_delay = ((ThreadInfo *)p)->delay;
	DWORD m_persist = ((ThreadInfo *)p)->persist;
	DWORD m_id = ((ThreadInfo *)p)->tid;
	sleep(m_delay);
	printf("Input thread %d sends writing request to buffer_1\n", m_id);
	while (n1 == N1)
		WaitForSingleObject(buf_1_operate_sema, -1);
	printf("Input thread %d begins writing to buffer_1\n", m_id);
	sleep(m_persist);
	printf("Input thread %d finishs writing to buffer_1\n\n", m_id);
	n1++;
	printBufferState();
	ReleaseSemaphore(buf_1_sema, 1, nullptr);
	return;
}
#endif