#include <iostream>
#include <pthread.h>
#include <unistd.h>

using std::cout;
using std::endl;

void *thread_main(void *arg);

int main()
{
	pthread_t t_id;
	int threadParam = 5;

	if (pthread_create(&t_id, NULL, thread_main, (void *)&threadParam) != 0) {
		cout << "Thread create error." << endl;
		return -1;
	}

	sleep(10);
	cout << "End" << endl;

	return 0;
}

void *thread_main(void *arg)
{
	int i;
	int cnt = *((int *)arg);
	for (i = 0; i < cnt; ++i) {
		sleep(1);
		cout << "Running thread." << endl;
	}

	return NULL;
}
