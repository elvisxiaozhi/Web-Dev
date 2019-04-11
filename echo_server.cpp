#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>

using std::string;
using std::cout;
using std::cin;
using std::endl;

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
	
	int i = 0, strLen;
	for (i = 0; i < 5; ++i) {
		clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
		if (clientSocket == -1) {
			cout << "accept error" << endl;
		}	
		else {
			cout << "Connected client: " << i + 1 << endl;
		}

		while ((strLen = read(clientSocket, message, 1024)) != 0) {
			write(clientSocket, message, strLen);
		}		

		close(clientSocket);
	}
	
	close(serverSocket);

	return 0;
}
