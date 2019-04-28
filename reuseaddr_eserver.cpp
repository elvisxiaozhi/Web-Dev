#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[])
{
	int servSock, clntSock;
	char message[30];
	int option, strLen;
	socklen_t optLen, clntAddrSz;
	struct sockaddr_in servAddr, clntAddr;

	if (argc != 2) {
		cout << "error!" << endl;
	}

	servSock = socket(PF_INET, SOCK_STREAM, 0);
	optLen = sizeof(option);
	option = 1; //true
	setsockopt(servSock, SOL_SOCKET, SO_REUSEADDR, (void *)&option, optLen);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family	= AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));

	bind(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr));
	listen(servSock, 5);

	clntAddrSz = sizeof(clntAddr);
	clntSock = accept(servSock, (struct sockaddr *)&clntAddr, &clntAddrSz);
	
	while ((strLen = read(clntSock, message, sizeof(message))) != 0) 
		write(clntSock, message, strLen);
		write(1, message, strLen);

	close(clntSock);
	close(servSock);

	return 0;	
}
