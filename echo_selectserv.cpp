#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <cstring>

using std::cout;
using std::endl;

const int BUFF_SIZE = 100;

int main(int argc, char *argv[])
{
	int servSock, clntSock;
	struct sockaddr_in servAddr, clntAddr;
	struct timeval timeout;
	fd_set reads, cpyReads;
	socklen_t adrSz;
	int fdMax, strLen, fdNum, i;
	char buf[BUFF_SIZE];

	if (argc != 2) {
		cout << "Arguments issue." << endl;
		exit(1);
	}

	servSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));

	if (bind(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) == -1) {
		cout << "Bind error." << endl;
		exit(1);
	}
	if (listen(servSock, 5) == -1) {
		cout << "listen error" << endl;
		exit(1);
	}

	FD_ZERO(&reads);
	FD_SET(servSock, &reads);
	fdMax = servSock;

	while (true) {
		cpyReads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;

		if ((fdNum = select(fdMax + 1, &cpyReads, 0, 0, &timeout)) == -1) {
			break;
		}
		if (fdNum == 0) {
			continue;
		}

		for (i = 0; i < fdMax + 1; ++i) {
			if (FD_ISSET(i, &cpyReads)) {
				if (i == servSock) {
					adrSz = sizeof(clntAddr);
					clntSock = accept(servSock, (struct sockaddr *)&clntAddr, &adrSz);
					FD_SET(clntSock, &reads);
					if (fdMax < clntSock) {
						fdMax = clntSock;
					}
					cout << "Connect client: " << clntSock << endl;
				}
				else {
					strLen = read(i, buf, BUFF_SIZE);
					if (strLen == 0) {
						FD_CLR(i, &reads);
						close(i);
						cout << "Closed client: " << i << endl;
					}	
					else {
						write(i, buf, strLen);
					}
				}
			}
		}
	}

	close(servSock);
	return 0;
}
