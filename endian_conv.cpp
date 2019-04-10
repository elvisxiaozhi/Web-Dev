#include <iostream>
#include <arpa/inet.h>
#include <iomanip>

using std::cout;
using std::endl;
using std::hex;

int main() 
{
	unsigned short hostPort = 0x1234;
	unsigned short netPort;
	unsigned long hostAddr = 0x12345678;
	unsigned long netAddr;

	netPort = htons(hostPort);
	netAddr = htonl(hostAddr);

	cout << "Host ordered port: " << hex << "0x" << hostPort << endl;
	cout << "Network ordered port: " << hex << "0x" << netPort << endl;
	cout << "Host ordered address: " << hex << "0x" << hostAddr << endl;
	cout << "Network ordered address: " << hex << "0x" << netAddr << endl;

	return 0;
}
