#if 0
/*有一座独木桥
桥上不允许两车交会
允许同方向多辆车依次通行。

如何进行交通控制？*/
/*
想复杂了，开始准备两个方向分别通行一定数量汽车后换另一个方向通行
但有一个问题，如果一边剩下车的数量不能凑齐一组那他们要一直等待吗
因此这就成了一个简单的同步问题，设定为一个方向通行一定时间，在程序中
以sleep(m_persist)体现*/
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
	char direc;//S represent north to south, R represents south to north
	double delay;
	double persist;
};
int pass_count = 0;
int south_to_north_count = 0, north_to_south_count = 0;
HANDLE north_to_south_sema, south_to_north_sema,direction_sema,count_sema;
CRITICAL_SECTION single_pass;
bool north_to_south_cannot_pass = false, south_to_north_cannot_pass = false;
const int TOTALTHREAD = 100;
void northToSouth(void *p);
void southToNorth(void *p);
void printThread(void *p);
void printBufferState();

int main(void) {
	DWORD thread_count = 0;
	DWORD thread_ID;
	ThreadInfo thread_info[TOTALTHREAD];
	HANDLE thread[TOTALTHREAD];
	direction_sema = CreateSemaphore(nullptr, 0, 1, (LPCSTR)"semaphore_for_passing_direction");
	north_to_south_sema = CreateSemaphore(nullptr, 0, 3, (LPCTSTR)"semaphore_for_north_to_south");
	south_to_north_sema = CreateSemaphore(nullptr, 3, 3, (LPCTSTR)"semaphore_for_south_to_north");
	count_sema = CreateSemaphore(nullptr, 0, 1, (LPCTSTR)"semaphore_for_two_count");
	InitializeCriticalSection(&single_pass);
	fstream infile;
	infile.open("text.txt");
	if (!infile) {
		printf("Error in open file\n");
		cin.get();
		return -1;
	}
	while (infile) {
		infile >> thread_info[thread_count].tid;
		infile >> thread_info[thread_count].direc;
		infile >> thread_info[thread_count].delay;
		infile >> thread_info[thread_count].persist;
		thread_count++;
	}
	for (int i = 0; i < thread_count; ++i) {
		if (thread_info[i].direc == 'S' || thread_info[i].direc == 's')
			thread[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(northToSouth),
				&thread_info[i], 0, &thread_ID);
		else
			thread[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(southToNorth),
				&thread_info[i], 0, &thread_ID);
	}
	WaitForMultipleObjects(thread_count, thread, true, -1);
	printf("All north to south, south to north threads have finished operating\n");

	cin.get();
	return 0;
}
void printBufferState() {
	printf("north to south: %d\n", north_to_south_count);
	printf("north_to_south_cannot_pass:%d\n", north_to_south_cannot_pass);
	printf("south to north: %d\n", south_to_north_count);
	printf("south_to_north_cannot_pass:%d\n", south_to_north_cannot_pass);
	return;
}
void northToSouth(void *p) {
	DWORD m_delay = ((ThreadInfo *)p)->delay;
	DWORD m_persist = ((ThreadInfo *)p)->persist;
	int m_id = ((ThreadInfo *)p)->tid;
	printf("north to south Thread %d sends pass request to bridge\n", m_id);
	sleep(m_delay);
	while (north_to_south_cannot_pass==true)
		WaitForSingleObject(count_sema,-1);
	WaitForSingleObject(north_to_south_sema, -1);
	EnterCriticalSection(&single_pass);
	printf("North to south thread %d begins passing\n", m_id);
	sleep(m_persist);
	south_to_north_count++;
	if (south_to_north_count % 3 == 0) {
		north_to_south_cannot_pass = true;
		south_to_north_cannot_pass = false;
	}
	printf("North to south thread %d finishes passing\n", m_id);
	printBufferState();
	LeaveCriticalSection(&single_pass);
	ReleaseSemaphore(south_to_north_sema, 3, nullptr);
	if (south_to_north_cannot_pass == false) {
	
		ReleaseSemaphore(direction_sema, 1, nullptr);
	}
}
void southToNorth(void *p) {
	DWORD m_delay = ((ThreadInfo *)p)->delay;
	DWORD m_persist = ((ThreadInfo *)p)->persist;
	int m_id = ((ThreadInfo *)p)->tid;
	printf("South to north thread %d sends passing request to bridge\n", m_id);
	sleep(m_delay);
	while (south_to_north_cannot_pass==true)
		WaitForSingleObject(direction_sema,-1);
	WaitForSingleObject(south_to_north_sema, -1);
	EnterCriticalSection(&single_pass);
	printf("south to north thread %d begins passing\n", m_id);
	sleep(m_persist);
	north_to_south_count++;
	if (north_to_south_count % 3 == 0) {
		south_to_north_cannot_pass = true;
		north_to_south_cannot_pass = false;
	}
	printf("south to north thread %d finishs passing\n\n", m_id);
	printBufferState();
	LeaveCriticalSection(&single_pass);
	ReleaseSemaphore(north_to_south_sema, 3, nullptr);
	if (north_to_south_cannot_pass == false) {
		
		ReleaseSemaphore(count_sema, 1, nullptr);
	}
		
}
/*
text.txt
1	S	1	2
2	N	3	4
3	S	5	6
4	S	7	8
5	N	9	10
6	N	10	9
7	N	8	7
8	S	6	5
9	N	4	3
10	S	2	1
*/
#endif