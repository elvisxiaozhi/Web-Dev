#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

const int BUF_SIZE = 30;

int main()
{
	int fds[2];
	char str[] = "Hello?";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds);
	pid = fork();
	if (pid == 0) {
		write(fds[1], str, sizeof(str));
	}
	else {
		read(fds[0], buf, BUF_SIZE);
		cout << buf << endl;
	}

	return 0;
}
