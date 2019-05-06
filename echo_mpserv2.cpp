#include <iostream>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fstream>

using std::cout;
using std::endl;
using std::ofstream;

const int BUF_SIZE = 100;

void readChildProc(int sig);

int main(int argc, char *argv[])
{
	int servSock, clntSock;
	int fds[2];
	pid_t pid;
	char buf[BUF_SIZE];
	struct sockaddr_in sevrAdr, clntAddr;
	struct sigaction act;
	socklen_t adrSZ;
	int strLen, state;

	if (argc != 2) {
		cout << "Argument issue." << endl;
		exit(1);
	}

	act.sa_handler = readChildProc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	state = sigaction(SIGCHLD, &act, 0);

	servSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&sevrAdr, 0, sizeof(sevrAdr));
	sevrAdr.sin_family = AF_INET;
	sevrAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	sevrAdr.sin_port = htons(atoi(argv[1]));

	if (bind(servSock, (struct sockaddr *)&sevrAdr, sizeof(sevrAdr)) == -1) {
	cout << "Connect error." << endl;	
	};
	if (listen(servSock, 5) == -1) {
		cout << "Listen error." << endl;
	}

	pipe(fds);
	pid = fork();
	
	if (pid == 0) {
		std::ofstream fp;
		fp.open("echo_msg.txt");
		char msgBuf[BUF_SIZE];
		int i, len;

		for (i = 0; i < 10; ++i) {
			len = read(fds[0], msgBuf, BUF_SIZE);
			fp <<  msgBuf << endl;
		}

		fp.close();
		return 0;
	}

	while (1) {
		adrSZ = sizeof(clntAddr);
		clntSock = accept(servSock, (struct sockaddr *)&clntSock, &adrSZ);
		if (clntSock == -1) {
			continue;
		}
		else {
			cout << "New client connected..." << endl;
		}

		pid = fork();
		if (pid == 0) {
			close(servSock);
			while ((strLen = read(clntSock, buf, BUF_SIZE)) != 0) {
				write(clntSock, buf, strLen);
				write(fds[1], buf, strLen);
			}
			close(clntSock);
			cout << "Client disconnected..." << endl;
			return 0;
		}
		else {
			close(clntSock);
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

















