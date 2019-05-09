#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fstream>

using std::cout;
using std::endl;
using std::fstream;

const int TTL = 64;
const int BUF_SIZE = 255;

int main(int argc, char *argv[])
{
	int sendSock;
	struct sockaddr_in mulAdr;
	int timeLive = TTL;
	fstream fp;
	char buf[BUF_SIZE];

	sendSock = socket(PF_INET, SOCK_DGRAM, 0);
	memset(&mulAdr, 0, sizeof(mulAdr));
	mulAdr.sin_family = AF_INET;
	mulAdr.sin_addr.s_addr = inet_addr(argv[1]);
	mulAdr.sin_port = htons(atoi(argv[2]));

	setsockopt(sendSock, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&timeLive, sizeof(timeLive));
	fp.open("news.txt");

	std::string readStr;
	while (getline(fp, readStr)) {
		strcpy(buf, readStr.c_str());	
		sendto(sendSock, buf, strlen(buf), 0, (struct sockaddr *)&mulAdr, sizeof(mulAdr));
		sleep(2);
	}

	fp.close();
	close(sendSock);

	return 0;
}
