#include <iostream>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using std::cout;
using std::endl;
using std::string;

const int BUF_SIZE = 30;

void readChildProc(int sig);

int main(int argc, char *argv[])
{
	int servSock, clntSock;
	struct sockaddr_in servAdr, clntAdr;

	pid_t pid;
	struct sigaction act;
	socklen_t adrSz;
	int strLen, state;
	char buf[BUF_SIZE];

	if (argc != 2) {
		cout << "Argument error." << endl;
		exit(1);
	}

	act.sa_handler = readChildProc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	state = sigaction(SIGCHLD, &act, 0);

	servSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));

	if (bind(servSock, (struct sockaddr *)&servAdr, sizeof(servAdr)) == -1) {
		cout << "Bind error." << endl;
	}

	if (listen(servSock, 5) == -1) {
		cout << "Listen error." << endl;
	}

	while (true) {
		adrSz = sizeof(clntAdr);
		clntSock = accept(servSock, (struct sockaddr *)&clntAdr, &adrSz);

		if (clntSock == -1) {
			continue;
		}
		else {
			cout << "New client connected." << endl;
			pid = fork();

			if (pid == -1) {
				close(clntSock);
				continue;
			}
			if (pid == 0) {
				close(servSock);
				while ((strLen = read(clntSock, buf, BUF_SIZE)) != 0) {
					write(clntSock, buf, strLen);
				} 

				close(clntSock);
				cout << "Client disconnected." << endl;

				return 0;
			}
			else {
				close(clntSock);		
			}
		}
	}

	close(servSock);

	return 0;
}

void readChildProc(int sig)
{
	pid_t pid;
	int status;
	pid = waitpid(-1, &status, WNOHANG);
	cout << "Remove proc id: " << pid << endl;
}
