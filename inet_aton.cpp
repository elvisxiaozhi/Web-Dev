#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
using std::hex;

int main()
{
	string addr = "127.232.124.79";
	struct sockaddr_in addrInet;

	if (!inet_aton(addr.c_str(), &addrInet.sin_addr)) {
		cout << "error" << endl;
	}
	else {
		cout << "Network ordered integer addr: " << "0x" << hex << addrInet.sin_addr.s_addr << endl;
	}

	return 0;
}
