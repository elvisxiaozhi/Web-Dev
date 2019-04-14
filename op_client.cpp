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

	int result, opndCnt, i;
	cout << "Operand count: ";
	cin >> opndCnt;
	message[0] = (char)opndCnt;

	for (i = 0; i < opndCnt; ++i) {
		cout << "Operand " << i + 1 << ": ";
		int inputNum;
		cin >> inputNum;
		memcpy(&message[i * 4 + 1], &inputNum, sizeof(inputNum));
	}

	cout << "Operator: ";
	char op;
	cin >> op;
	message[opndCnt * 4 + 1] = op;

	write(sock, message, opndCnt * 4 + 2);
	read(sock, &result, 4);
	
	cout << "Result: " << result << endl;

	close(sock);

	return 0;
}

