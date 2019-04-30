#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using std::cout;
using std::endl;

int main()
{
	int status;
	pid_t pid = fork();
	if (pid == 0)
		return 3;
	else {
		cout << "Child PID: " << pid << endl;
		pid = fork();
		if (pid == 0)
			exit(7);
		else {
			cout << "Child PID: " << pid << endl;
			wait(&status);
			if (WIFEXITED(status))
				cout << "Child send one: " << WEXITSTATUS(status) << endl;
	
		     wait(&status);                                                	
             if (WIFEXITED(status))
             	cout << "Child send one: " << WEXITSTATUS(status) << endl;

			 sleep(10);
		}
	}

	return 0;
}
