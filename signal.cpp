#include <iostream>
#include <unistd.h>
#include <csignal>

using std::cout;
using std::endl;

void timeOut(int sig)
{
	if (sig == SIGALRM)
		cout << "Time out." << endl;

	alarm(2);
}

void keyControl(int sig)
{
	if (sig == SIGINT)
		cout << "Key pressed." << endl;
}

int main()
{
	int i;
	signal(SIGALRM, timeOut);
	signal(SIGINT, keyControl);
	alarm(2);

	for (i = 0; i < 3; ++i) {
		cout << "waiting..." << endl;
		sleep(100);
	}

	return 0;
}
