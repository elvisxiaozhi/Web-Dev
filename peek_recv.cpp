#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using std::cout;
using std::endl;

#define BUF_SIZE 32

int main(int argc, char *argv[])
{
	int server_sock;
	int client_sock;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t client_addr_size;

	char message[BUF_SIZE];

	int str_len;
	
	server_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(argv[1]));
	
	bind( server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	listen(server_sock, 5);

	client_addr_size = sizeof(client_addr);
	client_sock = accept( server_sock, (struct sockaddr*)&client_addr,
						 &client_addr_size );

	while(1){
		str_len = recv(client_sock, message, sizeof(message)-1,
						MSG_PEEK | MSG_DONTWAIT);
		//设置PEEK选项并调用recv函数时，即使读取量输入缓冲中的数据也不会删除
		//MSG_DONTWAIT 以非阻塞方式验证待读数据存在与否
		if(str_len > 0) break;
	}

	message[str_len] = 0;
	cout << "Buffering " << sizeof(message) << " bytes: " << message << endl; 
	str_len = 0;
	memset(message, 0, BUF_SIZE);
	str_len = recv(client_sock, message, sizeof(message)-1, 0);
	message[str_len] = 0;
	cout << "Read again: " << message << endl;

	close(client_sock); 
	close(server_sock);

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
