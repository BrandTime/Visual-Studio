#if 0
#include<pthread.h>
#include<Windows.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
using namespace std;

struct ThreadInfo {
	int tid;
	char role;
	DWORD delay;
	DWORD persit;
};
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notFull = PTHREAD_COND_INITIALIZER;
pthread_cond_t notEmpty = PTHREAD_COND_INITIALIZER;
int N = 20;
int buffer[20];
int in = 0, out = 0;
int totalCount = 0;
#define sleep(n) Sleep(n*1000)
void put(int o);
int get();
void *consumer_thread(void *arg) {
	int id = (int)arg;
	while (true) {
		int x = get();
		fprintf(stdout, "consumer %d:%d\n", id, x);
		sleep(2);
	}
	return ((void *)0);
}
void *producer_thread(void *arg) {
	int id = (int)arg;
	for (int i = 0;; i++) {
		int x = id * 1000 + i;
		fprintf(stdout, "producer %d:%d\n", id, x);
		put(x);
		sleep(1);
	}
	return ((void *)0);
}

int main(void) {
	for (int i = 1; i <= 3; ++i) {
		pthread_t tid;
		int error = pthread_create(&tid, nullptr, producer_thread, (void *)i);
		if (error != 0)
			printf("Cannot create thread:%s", strerror(error));
	}
	for (int i = 1; i <= 2; ++i) {
		pthread_t pid;
		int error = pthread_create(&pid, nullptr, consumer_thread, (void *)i);
		if (error != 0)
			printf("Cannot create thread:%s", strerror(error));
	}
	
	system("pause");
	return 0;
}
void put(int o) {
	pthread_mutex_lock(&lock);
	while (totalCount == N)
		pthread_cond_wait(&notFull,&lock);
	buffer[in] = o;
	in = (in + 1) % N;
	totalCount++;
	pthread_mutex_unlock(&lock);
	pthread_cond_signal(&notEmpty);
}
int get() {
	pthread_mutex_lock(&lock);
	while (totalCount == 0)
		pthread_cond_wait(&notEmpty, &lock);
	int o = buffer[out];
	out = (out + 1) % N;
	totalCount--;
	pthread_mutex_unlock(&lock);
	pthread_cond_signal(&notFull);
	return o;
}
#endif