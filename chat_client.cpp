#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

using std::cout;
using std::endl;
using std::string;

const int BUFF_SIZE = 100;
const int NAME_SIZE = 20;

void *send_msg(void *msg);
void *recv_msg(void *msg);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUFF_SIZE];

int main(int argc, char *argv[])
{
	int sock_server;
	struct sockaddr_in addr_server;
	pthread_t pthread_id_send, pthread_id_recv;	
	void *thread_ret;

	if(argc!=4){ 
		cout << "Argument issue." << endl;
		exit(1);
	}

	memset(name, 0, sizeof(name));
	string strName = "[" + string(argv[3]) + "]";
	strcpy(name, strName.c_str());

	sock_server = socket(PF_INET, SOCK_STREAM, 0);

	memset(&addr_server, 0, sizeof(addr_server));
	addr_server.sin_family = AF_INET;
	addr_server.sin_addr.s_addr = inet_addr(argv[1]);
	addr_server.sin_port = htons(atoi(argv[2]));
	if(-1 == connect(sock_server, (struct sockaddr*)&addr_server, sizeof(addr_server))){
		cout << "Connect error." << endl;
	}
	
	pthread_create(&pthread_id_send, NULL, send_msg, (void*)&sock_server);
	pthread_create(&pthread_id_recv, NULL, recv_msg, (void*)&sock_server);
	pthread_join(pthread_id_send, &thread_ret);
	pthread_join(pthread_id_recv, &thread_ret);

	cout << "End of client!" << endl;
	
	close(sock_server);
	return 0;
}

void *send_msg(void *arg)
{
	int sock = *((int *)arg);
	char name_msg[NAME_SIZE+BUFF_SIZE];
	while(1){
		//puts("Input Message(Q quit):");
		fgets(msg, BUFF_SIZE, stdin);
		if( !strcmp(msg, "q\n") || !strcmp(msg, "Q\n") ){
			fputs("Quit!\n", stderr);
			close(sock);
			exit(0);
		}
		sprintf(name_msg, "%s %s", name, msg);
		write(sock, name_msg, strlen(name_msg));
	}
	return NULL;
}
void *recv_msg(void *arg)
{
	int sock = *((int *)arg);
	char name_msg[NAME_SIZE+BUFF_SIZE];
	int str_len;
	while(1){
		str_len = read(sock, name_msg, NAME_SIZE + BUFF_SIZE - 1);
		if(str_len < 0) return (void*)-1;
		
		cout << name_msg;
		memset(name_msg, 0, sizeof(name_msg));
	}
	return NULL;
}
