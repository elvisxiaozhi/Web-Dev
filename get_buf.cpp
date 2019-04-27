#include <iostream>
#include <unistd.h>
#include <sys/socket.h>

using std::cout;
using std::endl;

int main() 
{
	int sock, sndBuf, rcvBuf, state;
	socklen_t len;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	len = sizeof(sndBuf);
	state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&sndBuf, &len);

	len = sizeof(rcvBuf);
	state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *)&rcvBuf, &len);

	cout << "Input buffer size: " << rcvBuf << endl;
	cout << "Output buffer size: " << sndBuf << endl;

	return 0;
}
