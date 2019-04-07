#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using std::string;
using std::cout;
using std::endl;
using std::cin;

int main()
{
	int sock, strLen;
	char message[255];
	struct sockaddr_in serverAddr;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serverAddr, 0, sizeof(serverAddr));

	string port;
	cout << "What is the port: ";
	getline(cin, port); 

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(atoi(port.c_str()));

	connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

	strLen = read(sock, message, 255);
	cout << "Message from server: " << message << endl;
	
	close(sock);

	return 0;
}

