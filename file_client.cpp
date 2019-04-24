#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <netinet/in.h>
#include <arpa/inet.h>

using std::ofstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;

#define BUF_SIZE 30

int main()
{
	int server_sock;
	struct sockaddr_in server_addr;

	char buf[BUF_SIZE], message[BUF_SIZE];
	int read_count = 0;
	ofstream fp;
	fp.open("received.txt");	
	
	server_sock = socket(PF_INET, SOCK_STREAM, 0);
	
	cout << "What's the port: ";
	string port;
	getline(cin, port);	

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(atoi(port.c_str()));

	if( -1 == connect(server_sock, (struct sockaddr*)&server_addr,
					  sizeof(server_addr)) ){
			cout << "Connect error" << endl;
	}

	while((read_count = read(server_sock, message, BUF_SIZE))){
		fp << buf;
	}
	fp.close();
	cout << "File received from server" << endl;
	cout << buf << endl;
	//返回消息，若服务器端未断开输入流则可以接收此消息
	strcpy(message, "File Received. Thank you!");
	write(server_sock, message, strlen(message));

	close(server_sock);

	return 0;
}
