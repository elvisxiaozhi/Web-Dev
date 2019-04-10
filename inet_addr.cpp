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
	string addr1 = "1.2.3.4";
	string addr2 = "1.2.3.256";

	unsigned long convAddr = inet_addr(addr1.c_str());

	if (convAddr == INADDR_NONE) {
		cout << "Error" << endl;
	}
	else {
		cout << "Network ordered integer addr: " << "0x" << hex << convAddr << endl;		
	}

	convAddr = inet_addr(addr2.c_str());

     if (convAddr == INADDR_NONE) {
		cout << "Error" << endl;
 	 }  
	 else {
		cout << "Network ordered integer addr: " << "0x" << hex << convAddr << endl;
	 }

	return 0;
}
