#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using std::cout;
using std::endl;
using std::string;

int main()
{
	int fd;
	string buf = "Let's go!\n";
	fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC);
	write(fd, buf.c_str(), buf.size());
}
