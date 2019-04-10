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
	struct sockaddr_in addr1, addr2;
	char *strPtr;
	char strArr[20];

	addr1.sin_addr.s_addr = htonl(0x1020304);
	addr2.sin_addr.s_addr = htonl(0x1010101);

	strPtr = inet_ntoa(addr1.sin_addr);
	strcpy(strArr, strPtr);

	cout << "Dotted-Decimal notation1: " << strPtr << endl;

	inet_ntoa(addr2.sin_addr);
	cout << "Dotted-Decimal notation2: " << strPtr << endl;
	cout << "Dotted-Decimal notation3: " << strArr << endl;

	return 0;
}
