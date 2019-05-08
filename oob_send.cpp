#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using std::cout;
using std::endl;

#define BUFF_SIZE 32

int main(int argc, char *argv[])
{
	int sock_client;
	struct sockaddr_in recv_addr;

	memset(&recv_addr, 0, sizeof(recv_addr));
	recv_addr.sin_family = AF_INET;
	recv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	recv_addr.sin_port = htons(atoi(argv[2]));

	sock_client = socket(PF_INET, SOCK_STREAM, 0);
	if(-1 == connect(sock_client, (struct sockaddr*)&recv_addr, sizeof(recv_addr))){
		cout << "Connect error" << endl;
	}
	
	write(sock_client, "123", strlen("123"));
	send(sock_client, "4", strlen("4"), MSG_OOB);
	write(sock_client, "567", strlen("567"));
	send(sock_client, "890", strlen("890"), MSG_OOB);

	close(sock_client);
	return 0;
}
