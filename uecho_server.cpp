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
	int serverSocket;
	struct sockaddr_in serverAddr, clientAddr;
	int strLen;
   	socklen_t clientAddrSize;

	char message[30];	

	serverSocket = socket(PF_INET, SOCK_DGRAM, 0);

	cout << "What's the port: ";
	string port;
	getline(cin, port);

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(atoi(port.c_str()));

	bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

	while (true) {
		clientAddrSize = sizeof(clientAddr);	
		strLen = recvfrom(serverSocket, message, 30, 0, (struct sockaddr *)&clientAddr, &clientAddrSize);
		sendto(serverSocket, message, strLen, 0, (struct sockaddr *)&clientAddr, clientAddrSize);
	}
	close(serverSocket);

	return 0;
}
