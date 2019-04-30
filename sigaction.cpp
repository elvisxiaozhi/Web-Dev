#include <iostream>
#include <unistd.h>
#include <signal.h>

using std::cout;
using std::endl;

void timeOut(int sig)
{
	if (sig == SIGALRM)
		cout << "Time out." << endl;

	alarm(2);
}

int main()
{
	int i;
	struct sigaction act;
	act.sa_handler = timeOut;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, 0);

	alarm(2);

	for (i = 0; i < 3; ++i)
		cout << "waiting..." << endl;
		sleep(100);

	return 0;
}
