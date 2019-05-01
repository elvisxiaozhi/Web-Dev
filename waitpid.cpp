#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

using std::cout;
using std::endl;

int main()
{
	int status;
	pid_t pid = fork();
	if (pid == 0) {
		sleep(5);
		exit(24);
	}
	else {
		while (!waitpid(-1, &status, WNOHANG)) {
			sleep(1);
			cout << "Sleep 1 sec." << endl;
		}

		if (WIFEXITED(status))
			cout << "Child send: " << WEXITSTATUS(status) << endl;
	}

	return 0;
}
