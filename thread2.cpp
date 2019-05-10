#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstring>

using std::cout;
using std::endl;

void *thread_main(void *arg);

int main()
{
	pthread_t t_id;
	int threadParam = 5;
	void *thr_ret;

	if (pthread_create(&t_id, NULL, thread_main, (void *)&threadParam) != 0) {
		cout << "Thread create error." << endl;
		return -1;
	}

	if (pthread_join(t_id, &thr_ret) != 0) {
		cout << "Join error." << endl;
		return -1;
	}

	cout << "Thread return message: " << (char *)thr_ret << endl;
	free(thr_ret);

	return 0;
}

void *thread_main(void *arg)
{
	int i;
	int cnt = *((int *)arg);
	char *msg = (char *)malloc(sizeof(char)*50);
	strcpy(msg, "Hello, I am a thread.\n");

	for (i = 0; i < cnt; ++i) {
		sleep(1);
		cout << "Running thread." << endl;
	}

	return (void *)msg;
}
