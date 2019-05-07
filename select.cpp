#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

using std::cout;
using std::endl;

const int BUFF_SIZE = 30;

int main()
{
	fd_set reads, temps;
	struct timeval timeout;
	char buf[BUFF_SIZE];
	int result, strLen;

	FD_ZERO(&reads);
	FD_SET(0, &reads);

	while (true) {
		temps = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		result = select(1, &temps, 0, 0, &timeout);
		if (result == -1) {
			cout << "select error" << endl;
			break;
		}
		else if (result == 0) {
			cout << "Timeout" << endl;
		}
		else {
			if (FD_ISSET(0, &temps)) {
				strLen = read(0, buf, BUFF_SIZE);
				buf[strLen] = 0;
				cout << "Message from console: " << buf << endl;
			}
		}
	}

	return 0;
}
