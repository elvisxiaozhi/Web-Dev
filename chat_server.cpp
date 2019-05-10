#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

using std::cout;
using std::endl;

#define BUFF_SIZE 100 
#define CLIENT_MAX 256 

void *client_handler(void *arg);
void send_msg(char *msg, int len);

int count_client = 0;
int socks_client[CLIENT_MAX];
pthread_mutex_t mutex;

int main(int argc, char *argv[])
{
	int sock_server;
	int sock_client;

	struct sockaddr_in addr_server;
	struct sockaddr_in addr_client;
	socklen_t size_addr_client;

	pthread_t pthread_id;	

	if(argc!=2){ 
		cout << "Argument issue." << endl;
		exit(1);
	}
	
	pthread_mutex_init(&mutex, NULL);
	sock_server = socket(PF_INET, SOCK_STREAM, 0);
	
	memset(&addr_server, 0, sizeof(addr_server));
	addr_server.sin_family = AF_INET;
	addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_server.sin_port = htons(atoi(argv[1]));
	
	if (-1 == bind( sock_server, (struct sockaddr*)&addr_server, 
				sizeof(addr_server)) ){
		cout << "Bind error." << endl;
	}

	if( -1 == listen(sock_server, 5) ){
		cout << "Listen error." << endl;
	}

	while (true){
		size_addr_client = sizeof(addr_client);
		sock_client = accept( sock_server, (struct sockaddr*)&addr_client, &size_addr_client);

		pthread_mutex_lock(&mutex);
		socks_client[count_client++] = sock_client;//Lock 访问公共代码区
		pthread_mutex_unlock(&mutex);

		pthread_create(&pthread_id, NULL, client_handler, (void *)&sock_client);
		pthread_detach(pthread_id);//销毁线程

		cout << "Client IP: " << inet_ntoa(addr_client.sin_addr) << endl; 
	} 

	close(sock_server);
	pthread_mutex_destroy(&mutex);
	
	return 0;
}

void *client_handler(void *arg)
{
	int sock_client = *((int *)arg);
	int str_len = 0, i;
	char msg[BUFF_SIZE];

	while((str_len = read(sock_client, msg, sizeof(msg))) != 0){
		send_msg(msg, str_len);
	}

	pthread_mutex_lock(&mutex);
	for(i=0; i<count_client; i++){//remove disconnencted client
		if(sock_client == socks_client[i]){
			while(i++ <= count_client-1){
				socks_client[i] = socks_client[i+1];
			}
			break;
		}
	}
	count_client--;
	pthread_mutex_unlock(&mutex);
	close(sock_client);

	return NULL;
}
void send_msg(char *msg, int len)//send message to all clients
{
	int i;
	pthread_mutex_lock(&mutex);
	for(i=0; i<count_client; i++){
		write(socks_client[i], msg, len);
	}
	pthread_mutex_unlock(&mutex);
}
