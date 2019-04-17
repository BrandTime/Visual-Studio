#if 0
#include<Windows.h>
#include<process.h>
#include<pthread.h>
#include<time.h>
#include<iostream>
using namespace std;

inline void sleep(int n) {
	Sleep(n * 1000);
}
const int N = 5;

//implement this problem with semaphoes
#if 0
HANDLE chop[N];
int readCount = 0;
void philosopherThread(void *p) {
	unsigned int i = (unsigned int)p;
	HANDLE ownChop[2];
	ownChop[0] = chop[i];
	ownChop[1] = chop[(i + 1) % N];
	WaitForMultipleObjects(2, ownChop, false, -1);
	printf("Philosopher %d is dining!\n", i+1);
	ReleaseSemaphore(chop[i], 1, nullptr);
	ReleaseSemaphore(chop[(i + 1) % N], 1, nullptr);
	printf("Philosopher %d is thinking!\n",i+1);
}
int main(void) {
	for (int i = 0; i < N; ++i)
		chop[i] = CreateSemaphore(nullptr, 1, 1, nullptr);
	HANDLE thread[N];
	for (int i = 0; i < N; ++i)
		thread[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(philosopherThread),
			(LPVOID *)i, 0, nullptr);
	WaitForMultipleObjects(N, thread, true, -1);
	printf("All philosopher finish dining\n");
	
	system("pause");
	return 0;
}
#endif

//implement this problem with monitor
//#if 0
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t philosopher[N];
int chop[N];
void *philosopherThread(void *i) {
	int id = (int)i;
	pthread_mutex_lock(&mutex);
	printf("philosopher %d is now hungry!\n", id);
	while (chop[id] != 0 && chop[(id + 1) % N] != 0)
		pthread_cond_wait(&philosopher[id], &mutex);
	printf("Philosopher %d is now eating!\n", id);
	sleep(3);
	chop[id] = 1;
	chop[(id + 1) % N] = 1;
	pthread_mutex_unlock(&mutex);
	pthread_mutex_lock(&mutex);
	printf("Philosopher %d is now thinking!\n", id);
	chop[id] = 0;
	chop[(id + 10 % N)] = 0;
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&philosopher[(id + 4) % N]);
	pthread_cond_signal(&philosopher[(id + 1) % N]);
	sleep(2);
	return (void *)i;
}

int main(void) {
	int i = 0;
	for (; i < N; ++i) {
		Schop[i] = 0;
		philosopher[i] = PTHREAD_COND_INITIALIZER;
	}
	for (i = 0; i < N; ++i) {
		pthread_t pid;
		int error=pthread_create(&pid, nullptr, philosopherThread, (void *)i);
		if (error)
			printf("Create thread failes!\n");
	}

	cin.get();
	return 0;
}
//#endif
#endif