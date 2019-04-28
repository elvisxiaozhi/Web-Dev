#include <iostream>
#include <unistd.h>
#include <sys/socket.h>

using std::cout;
using std::endl;

int main() 
{
	int sock;
	int sndBuf = 1024 * 3, rcvBuf = 1024 * 3;
   	int	state;
	socklen_t len;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *)&rcvBuf, sizeof(rcvBuf));
	state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&sndBuf, sizeof(sndBuf));

	len = sizeof(sndBuf);
	state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&sndBuf, &len);

	len = sizeof(rcvBuf);
	state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *)&rcvBuf, &len);

	len = sizeof(sndBuf);
	

	cout << "Input buffer size: " << rcvBuf << endl;
	cout << "Output buffer size: " << sndBuf << endl;

	return 0;
}
