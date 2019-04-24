#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>

using std::fstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;

int main()
{
	int serverSd, clientSd;
	fstream fp;
	struct sockaddr_in serverAddr, clientAddr;
   	socklen_t clientAddrSize;

	char buf[30];	

	fp.open("file_server.cpp");
	serverSd = socket(PF_INET, SOCK_STREAM, 0);

	cout << "What's the port: ";
	string port;
	getline(cin, port);

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(atoi(port.c_str()));

	bind(serverSd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	listen(serverSd, 5);
	clientAddrSize = sizeof(clientAddr);
	clientSd = accept(serverSd, (struct sockaddr*)&clientAddr, &clientAddrSize);

	while (true) {
		int i = 0;
		while (i < 30 && !fp.eof()) {
			fp.get(buf[i]);
			++i;
		}

		if (i < 30) {
			write(clientSd, buf, i);
			break;
		}

		write(clientSd, buf, 30);
	}

	shutdown(clientSd, SHUT_WR);
	read(clientSd, buf, 30);
	cout << "Message from client: " << buf << endl;

	fp.close();	
	close(clientSd); close(serverSd);


	return 0;
}
