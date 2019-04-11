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
	int sock;
	char message[1024];
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

	int strLen;
	while (true) {
		cout << "Input message(q|Q to quit): "; 
		string messageCp(message);
		getline(cin, messageCp);

		if (messageCp == "q" || messageCp == "Q")
			break;

		strcpy(message, messageCp.c_str());

		write(sock, message, strlen(message));	
		strLen = read(sock, message, 1024 - 1);
		message[strLen] = 0;
		cout << "Message from server: " << message << endl;
	}
	
	close(sock);

	return 0;
}

