#include <iostream>
#include <sys/uio.h>

using std::cout;
using std::endl;

int main()
{
	struct iovec vec[2];
	char buf1[] = "ABCD";
	char buf2[] = "1234";
	int strLen;

	vec[0].iov_base = buf1;
	vec[0].iov_len = 3;
	vec[1].iov_base = buf2;
	vec[1].iov_len = 4;

	strLen = writev(1, vec, 2);
	cout << endl;
	cout << "Write bytes: " << strLen << endl;
}
