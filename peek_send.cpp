#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	int server_sock;
	struct sockaddr_in server_addr;

	server_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(atoi(argv[2]));

	connect(server_sock, (struct sockaddr*)&server_addr,
					  sizeof(server_addr));

	write(server_sock, "123", strlen("123"));

	close(server_sock);

	return 0;
}
