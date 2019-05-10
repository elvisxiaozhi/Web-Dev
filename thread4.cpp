#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstring>

using std::cout;
using std::endl;

const int NUM_THREAD = 100;
long long num = 0;

void *threadInc(void *arg);
void *threadDes(void *arg);

int main()
{
	pthread_t thread_id[NUM_THREAD]; 
	int i;

	cout << "Size of long long: " << sizeof(long long) << endl;
	
	for (i = 0; i < NUM_THREAD; ++i) {
		if (i % 2 == 0) {
			pthread_create(&(thread_id[i]), NULL, threadInc, NULL);
		}
		else {
			pthread_create(&(thread_id[i]), NULL, threadDes, NULL);
		}
	}

	for (int i = 0; i < NUM_THREAD; ++i) {
		pthread_join(thread_id[i], NULL);
	}

	cout << "Result: " << num << endl;

	return 0;
}

void *threadInc(void *arg)
{
	int i;
	for (i = 0; i < 50000000; ++i) {
		num += 1;
	}

	return NULL;
}

void *threadDes(void *arg) 
{
	int i;
	for (i = 0; i < 50000000; ++i) {
		num -= 1;
	}

	return NULL;
}
