#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>

using std::string;

int main(int argc, char *argv[])
{
	int serverSocket, clientSocket;
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t clientAddrSize;
	
	string message = "Hello World";

	serverSocket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(atoi(argv[1]));

	bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	listen(serverSocket, 5);

	clientAddrSize = sizeof(clientAddr);
	clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);

	write(clientSocket, message.c_str(), sizeof(message));
	close(clientSocket);
	close(serverSocket);

	return 0;
}
