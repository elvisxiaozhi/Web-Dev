#include <iostream>
#include <unistd.h>
#include <sys/socket.h>

using std::cout;
using std::endl;

int main()
{
	int tcpSocket, udpSocket, sockType;
	socklen_t optLen;
	int state;

	optLen = sizeof(sockType);

	tcpSocket = socket(PF_INET, SOCK_STREAM, 0);
	udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

	cout << "SOCK_STREAM: " << SOCK_STREAM << endl;
	state = getsockopt(tcpSocket, SOL_SOCKET, SO_TYPE, (void *)&sockType, &optLen);
	cout << "The type of tcp socket: " << sockType << endl;

	cout << "SOCK_DGRAM: " << SOCK_DGRAM << endl;
	state = getsockopt(udpSocket, SOL_SOCKET, SO_TYPE, (void *)&sockType, &optLen);
	cout << "The type of udp socket: " << sockType << endl;

	return 0;
}
