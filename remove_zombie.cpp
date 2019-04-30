#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

using std::cout;
using std::endl;

void readChildProc(int sig)
{
	int status;
	pid_t id = waitpid(-1, &status, WNOHANG);
	if (WIFEXITED(status))
		cout << "Remove proc id: " << id << endl;
		cout << "Child send: " << WEXITSTATUS(status) << endl;
}

int main()
{
	pid_t pid;
	struct sigaction sig_act;

	sig_act.sa_handler = readChildProc; 
	sigemptyset(&sig_act.sa_mask);
	sig_act.sa_flags = 0;

	sigaction(SIGCHLD, &sig_act, 0);

	pid = fork();

	if(pid == 0){
		cout << "Hi, I am child process!" << endl;
		sleep(10);
		
		return 12;
	}
	else {
		cout << "Child proc id: " << pid << endl;
		pid = fork();
        
	   	if(pid == 0){                                      
         	cout << "Hi, I am child process!" << endl;
         	sleep(10);
         	
         	return 24;
		}
		else {
			int i;
			cout << "Child proc id: " << pid << endl;

			for (i = 0; i < 5; ++i)
				cout << "Waiting..." << endl;
				sleep(5);
		}
	}

	return 0;	
}
