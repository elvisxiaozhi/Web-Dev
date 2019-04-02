#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using std::string;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	int sock, strLen;
	char message[30];
	struct sockaddr_in serverAddr;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serverAddr, 0, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
	serverAddr.sin_port = htons(atoi(argv[2]));

	strLen = read(sock, message, sizeof(message) - 1);

	cout << "Message from server: " << message << endl;
	
	close(sock);

	return 0;
}

