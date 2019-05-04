#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using std::cout;
using std::endl;

const int BUF_SIZE = 30;

void readRoutine(int sock, char *buf);
void writeRoutine(int sock, char *buf);

int main(int argc, char *argv[])
{
	int sock;
	pid_t pid;
	char buf[BUF_SIZE];
	struct sockaddr_in sevrAdr;

	if (argc != 3) {
		cout << "Argument issue." << endl;
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&sevrAdr, 0, sizeof(sevrAdr));
	sevrAdr.sin_family = AF_INET;
	sevrAdr.sin_addr.s_addr = inet_addr(argv[1]);
	sevrAdr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr *)&sevrAdr, sizeof(sevrAdr)) == -1) {
	cout << "Connect error." << endl;	
	}

	pid = fork();
	if (pid == 0) {
		writeRoutine(sock, buf);
	}
	else {
		readRoutine(sock, buf);
	}

	close(sock);
	return 0;
}

void readRoutine(int sock, char *buf)
{
	while (true) {
		int strLen = read(sock, buf, BUF_SIZE);
		if (strLen == 0) {
			return;
		}

		buf[strLen] = 0;
		cout << "Message from server: " << buf << endl;
	}
}

void writeRoutine(int sock, char *buf) 
{
	while (true) {
		std::cin.getline(buf, BUF_SIZE);
        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n")) {
        	shutdown(sock, SHUT_WR);
        	return;
        }
        write(sock, buf, strlen(buf));
	}
}
