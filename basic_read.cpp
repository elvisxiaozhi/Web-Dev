#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using std::cout;
using std::endl;
using std::string;

int main()
{
	int fd;
	//string buf;
	char buf[14];

	fd = open("test.txt", O_RDONLY);
	//read(fd, buf.c_str(), buf.size());
	read(fd, buf, sizeof(buf) - 1);
	cout << buf << endl;

	close(fd);
}
