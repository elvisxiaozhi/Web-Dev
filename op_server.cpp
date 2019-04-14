#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>

using std::string;
using std::cout;
using std::cin;
using std::endl;

int calculate(int opnum, int opnds[], char op)
{
	int result = opnds[0], i;
	switch(op)
	{
		case '+':
			for (i = 1; i < opnum; ++i)
				result += opnds[i];
			break;
 		case '-':
			for (i = 1; i < opnum; ++i)
				result -= opnds[i];
			break;
 		case '*':
			for (i = 1; i < opnum; ++i)
				result *= opnds[i];
			break;

	}

	return result;
}

int main()
{
	int serverSocket, clientSocket;
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t clientAddrSize;

	char message[1024];	

	serverSocket = socket(PF_INET, SOCK_STREAM, 0);

	cout << "What's the port: ";
	string port;
	getline(cin, port);

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(atoi(port.c_str()));

	bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	listen(serverSocket, 5);

	clientAddrSize = sizeof(clientAddr);
	
	int i = 0, result;
	int opndCnt, recvLen, recvCnt;
	for (i = 0; i < 5; ++i) {
		opndCnt = 0;
		clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);

		if (clientSocket == -1) {
			cout << "accept error" << endl;
		}	
		else {
			cout << "Connected client: " << i + 1 << endl;
		}
		
		read(clientSocket, &opndCnt, 1);

		recvLen = 0;	
		while ((opndCnt * 4 + 1) > recvLen) {
			recvCnt = read(clientSocket, &message[recvLen], 2014 - 1);
			recvLen += recvCnt;
		}
		result = calculate(opndCnt, (int *)message, message[recvLen - 1]);	
		write(clientSocket, (char *)&result, sizeof(result));
		close(clientSocket);
	}
	
	close(serverSocket);

	return 0;
}
