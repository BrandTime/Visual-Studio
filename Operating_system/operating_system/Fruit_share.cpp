/*桌上有一个空盘，允许存放一只水果。爸爸可向盘中放苹果，
也可向盘中放桔子。儿子专等吃盘中桔子，女儿专等吃盘中的苹果。
规定当盘空时一次只能放一只水果供吃者取用，
请用PV信号量实现爸爸、儿子和女儿三个并发进程的同步。*/
#if 0
#include<pthread.h>
#include<Windows.h>
#include<iostream>
#include<fstream>
using namespace std;

pthread_cond_t apple = PTHREAD_COND_INITIALIZER;
pthread_cond_t orange = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
const int N = 8;
int appleCount = 0, orangeCount = 0;
inline void sleep(int n) {
	Sleep(n * 1000);
}
struct ThreadInfo {
	unsigned int id;
	char role;//o 代表父亲将桔子放到盘中，
	//a代表父亲将苹果放到盘中，s代表儿子到盘中取桔子，d代表女儿到盘中取苹果
	int interval;
};
void printBuffer() {
	printf("appleCount:%d\n", appleCount);
	printf("orangeCount:%d\n", orangeCount);
}
void *sonThread(void *i) {
	int ID = ((ThreadInfo *)i)->id;
	int inter = ((ThreadInfo *)i)->interval;
	pthread_mutex_lock(&mutex);
	printf("The son wanna eat orange...%d\n",ID);
	while (orangeCount == 0)
		pthread_cond_wait(&orange,&mutex);
	printf("The son begin eating orange...%d\n",ID);
	sleep(inter);
	printf("The son finish eating orange.%d\n\n",ID);
	orangeCount = 0;
	printBuffer();
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&orange);
	return (void *)0;
}
void *fatherThread(void *i) {
	int ID = ((ThreadInfo *)i)->id;
	int inter = ((ThreadInfo *)i)->interval;
	char m_role = ((ThreadInfo *)i)->role;
	pthread_mutex_lock(&mutex);
	printf("The father have prepared one fruit...%d\n",ID);
	if (m_role == 'o' || m_role == 'O') {
		while (orangeCount == 1)
			pthread_cond_wait(&orange, &mutex);
		sleep(inter);
		orangeCount = 1;
		printf("The father hava replenlish the plate.%d\n\n",ID);
		printBuffer();
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&orange);
	}
	else if(m_role=='a'||m_role=='A'){
		while (appleCount == 1)
			pthread_cond_wait(&apple, &mutex);
		sleep(inter);
		appleCount = 1;
		printf("The father hava replenlish the plate.%d\n\n",ID);
		printBuffer();
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&apple);
	}
	
	return (void *)0;;
}
void *daughterThread(void *i) {
	int ID = ((ThreadInfo *)i)->id;
	int inter = ((ThreadInfo *)i)->interval;
	pthread_mutex_lock(&mutex);
	printf("The daughter wanna eat apple...%d\n",ID);
	while (appleCount == 0)
		pthread_cond_wait(&apple, &mutex);
	printf("The daughter begin eating apple...%d\n",ID);
	sleep(inter);
	printf("The daughter finish eating apple.%d\n\n",ID);
	appleCount = 0;
	printBuffer();
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&apple);
	return (void *)0;
}

int main(void) {
	fstream file;
	file.open("text.txt");
	if (file.fail()) {
		cout << "File open error!" << endl;
		cin.get();
		return -1;
	}
	ThreadInfo thread[N];
	int i = 0;
	while (!file.eof()) {
		file >> thread[i].id;
		file >> thread[i].role;
		file >> thread[i++].interval;
	}
	for (i = 0; i < N; ++i) {
		pthread_t pid;
		if (thread[i].role == 's' || thread[i].role == 'S')
			pthread_create(&pid, nullptr, sonThread, (void *)&thread[i]);
		else if (thread[i].role == 'd' || thread[i].role == 'D')
			pthread_create(&pid, nullptr, daughterThread, (void *)&thread[i]);
		else
			pthread_create(&pid, nullptr, fatherThread, (void *)&thread[i]);
	}
	
	sleep(1000);
	return 0;
}
#endif