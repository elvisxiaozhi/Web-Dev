#include <iostream>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>

using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[])
{
	int i;
	struct hostent *host;
	struct sockaddr_in addr;

	if (argc != 2)
		cout << "error" << endl;

	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	host = gethostbyaddr((char *)&addr.sin_addr, 4, AF_INET);
	
	if (!host)
		cout << "get host error" << endl;

	cout << "Official name: " << host->h_name;
	
	for (i = 0; host->h_aliases[i]; ++i)
		cout << "Aliases: " << i + 1 << " " << host->h_aliases[i] << endl;

	cout << "Address type: " << ((host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6") << endl;

	for (i = 0; host->h_addr_list[i]; ++i)
		cout << "IP address: " << i + 1 << " " << inet_ntoa(*(struct in_addr *)host->h_addr_list[i]) << endl;

	return 0;	

}
