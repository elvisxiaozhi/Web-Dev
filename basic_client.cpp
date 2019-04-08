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
	int sock, readLen = 0, index = 0;
	char message[30];
	struct sockaddr_in serverAddr;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		cout << "sock error" << endl;
	}

	memset(&serverAddr, 0, sizeof(serverAddr));

	string port;
	cout << "What is the port: ";
	getline(cin, port); 

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(atoi(port.c_str()));

	if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
		cout << "connect error" << endl;
	}

	int strLen = 0;
	while ((readLen = read(sock, &message[++index], 1))) {
		if (readLen == -1) {
			cout << "read error" << endl;
		}

		strLen += readLen;
	};

	cout << "Message from server: " << message << endl;
	cout << "read call count: " << strLen << endl;

	close(sock);

	return 0;
}

