#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <signal.h>
#include <netinet/in.h>
#include <fcntl.h>

using std::cout;
using std::endl;

#define BUFF_SIZE 32

void error_handling(char *msg);
void oob_handler(int signo);

int sock_serv, sock_client;

int main(int argc, char *argv[])
{
	struct sockaddr_in addr_serv;
	socklen_t sz_addr_serv;
	struct sigaction act;
	char buff[BUFF_SIZE];
	ssize_t str_len;
	int state;

	act.sa_handler = oob_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	
	memset(&addr_serv, 0, sizeof(addr_serv));
	addr_serv.sin_family = PF_INET;
	addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_serv.sin_port = htons(atoi(argv[1]));

	sock_serv = socket(AF_INET, SOCK_STREAM, 0);
	bind(sock_serv, (struct sockaddr*)&addr_serv, sizeof(addr_serv));
	listen(sock_serv, 5);

	sz_addr_serv = sizeof(addr_serv);
	sock_client = accept(sock_serv, (struct sockaddr*)&addr_serv, &sz_addr_serv);

	//将文件描述符sock_client指向的套接字拥有者(F_SETOWN)改为ID为getpid()返回值的进程
	fcntl(sock_client, F_SETOWN, getpid());
	//将文件描述符sock_client指向的套接字引发的SIGURG信号处理进程变为ID为..
	state = sigaction(SIGURG, &act, 0);

	while((str_len = recv(sock_client, buff, sizeof(buff), 0)) != 0){
		if(str_len < 0) continue;
		buff[str_len] = 0;
		cout << buff << endl;
	}
	close(sock_client);
	close(sock_serv);
	return 0;
}
void oob_handler(int signo)
{
	int str_len;
	char buff[BUFF_SIZE];
	str_len = recv(sock_client, buff, sizeof(buff)-1, MSG_OOB);
	buff[str_len] = 0;
	cout << "Urgent message: " << buff << endl;
}
