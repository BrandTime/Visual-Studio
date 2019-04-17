#if 0
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<iostream>
using namespace std;

inline void sleep(unsigned long n) {
	Sleep(n * 1000);
	return;
}
struct ThreadInfo {
	int tid;
	char role;
	double delay;
	double persist;
};
int readCount = 0;
HANDLE Rmutex;//局部临界资源
CRITICAL_SECTION RW_mutex;

DWORD  WINAPI ReaderThread(LPVOID *p);
void WriterThread(void *p);
int main(void) {
	DWORD n_thread = 0;
	DWORD thread_ID;
	HANDLE h_thread[20];
	ThreadInfo thread_info[20];
	Rmutex = CreateMutex(NULL, FALSE, LPCSTR("mutex_for_readout"));
	ifstream infile;
	infile.open("D:\\Onedrive\\Opearating System\\test.txt");
	if (!infile) {
		cout << "Error in open file"<< endl;
		_getch();
		return -1;
	}
	while (infile) {
		infile >> thread_info[n_thread].tid;
		infile >> thread_info[n_thread].role;
		infile >> thread_info[n_thread].delay;
		infile >> thread_info[n_thread].persist;
		infile.get();
		++n_thread;
	}
	infile.close();
	InitializeCriticalSection(&RW_mutex);
	for (int i = 0; i < n_thread; ++i) {
		if (thread_info[i].role == 'r' || thread_info[i].role == 'R')
			h_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(ReaderThread),
				&thread_info[i], 0, &thread_ID);
		else
			h_thread[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(WriterThread),
				&thread_info[i], 0, &thread_ID);
	}
	DWORD wait_for_all = WaitForMultipleObjects(n_thread, h_thread, TRUE, -1);
	printf("All readers and writers have finished operating\n");
	_getch();

	return 0;
}
DWORD WINAPI ReaderThread(LPVOID *p) {
	DWORD m_delay;
	DWORD m_persist;
	int m_id;
	m_delay = ((ThreadInfo *)(p))->delay;
	m_persist = ((ThreadInfo *)p)->persist;
	m_id = ((ThreadInfo *)p)->tid;
	sleep(m_delay);
	printf("Reader thread %d send the reading request\n", m_id);
	DWORD waitForMutex = WaitForSingleObject(Rmutex, -1);
	readCount++;
	if (readCount == 1)
		EnterCriticalSection(&RW_mutex);
	ReleaseMutex(Rmutex);
	printf("Reader thread %d begins to read file\n", m_id);
	//cout << "Reader thread	" << m_id << "	begins to read file" << endl;//用cout输出较printf相比不是原子操作
	sleep(m_delay);
	printf("Reader thread %d finished reading file\n", m_id);
	waitForMutex = WaitForSingleObject(Rmutex, -1);
	readCount--;
	if (readCount == 0)
		LeaveCriticalSection(&RW_mutex);
	ReleaseMutex(Rmutex);

	return 0;
}
void WriterThread(void *p) {
	DWORD m_delay = ((ThreadInfo *)p)->delay;
	DWORD m_persist = ((ThreadInfo *)p)->persist;
	int m_id = ((ThreadInfo *)p)->tid;
	sleep(m_delay);
	printf("WRITER thread %d send the writing request\n", m_id);
	EnterCriticalSection(&RW_mutex);
	WaitForSingleObject(&RW_mutex, -1);
	printf("WRITER thread %d begins to write file\n", m_id);
	sleep(m_delay);
	printf("WRITER thread %d finished writing file\n", m_id);
	LeaveCriticalSection(&RW_mutex);
	return;
}
#endif