#include <iostream>
#include <sys/uio.h>

using std::cout;
using std::endl;

const int BUF_SIZE = 100;

int main()
{
	struct iovec vec[2];
	char buf1[BUF_SIZE] = {0,};
	char buf2[BUF_SIZE] = {0,};
	int strLen;

	vec[0].iov_base = buf1;
	vec[0].iov_len = 5;
	vec[1].iov_base = buf2;
	vec[1].iov_len = BUF_SIZE;

	strLen = readv(0, vec, 2);
	cout << "Read bytes: " << strLen << endl;
	cout << "First: " << buf1 << endl;
	cout << "Second: " << buf2 << endl;

	return 0;
}
