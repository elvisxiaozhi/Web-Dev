#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using std::cout;
using std::endl;

const int BUF_SIZE = 255;

int main(int argc, char *argv[])
{
	int recvSock, strLen;
	char buf[BUF_SIZE];
	struct sockaddr_in adr;
	struct ip_mreq joinAdr;

	recvSock = socket(PF_INET, SOCK_DGRAM, 0);
	memset(&adr, 0, sizeof(adr));
	adr.sin_family = AF_INET;
	adr.sin_addr.s_addr = htonl(INADDR_ANY);
	adr.sin_port = htons(atoi(argv[2]));

	bind(recvSock, (struct sockaddr *)&adr, sizeof(adr));

	joinAdr.imr_multiaddr.s_addr = inet_addr(argv[1]);
	joinAdr.imr_interface.s_addr = htonl(INADDR_ANY);

	setsockopt(recvSock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&joinAdr, sizeof(joinAdr));

	while (true) {
		strLen = recvfrom(recvSock, buf, BUF_SIZE - 1, 0, NULL, 0);
		if (strLen < 0)
			break;
		buf[strLen] = 0;
		cout << buf << endl;
	}

	close(recvSock);
	return 0;
}
