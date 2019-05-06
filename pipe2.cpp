#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

const int BUF_SIZE = 30;

int main()
{
	int fds[2];
	char str1[] = "Hello?";
	char str2[] = "Yes?";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds);
	pid = fork();
	if (pid == 0) {
		write(fds[1], str1, sizeof(str1));
		sleep(2);
		read(fds[0], buf, BUF_SIZE);
		cout << "Child proc output: " << buf << endl;
	}
	else {
		read(fds[0], buf, BUF_SIZE);
		cout << "Parent proc output: " << buf << endl;
		write(fds[1], str2, sizeof(str2));
		sleep(3);
	}

	return 0;
}
