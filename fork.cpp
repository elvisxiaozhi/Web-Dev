#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

int gval = 10;

int main()
{
	pid_t pid;
	int lval = 20;
	++gval, lval += 5;

	pid = fork();
	if (pid == 0)
		gval += 2, lval += 2;
	else 
		gval -= 2, lval -= 2;

	if (pid == 0)
		cout << "Children Proc: " << gval << "\t" << lval << endl;
	else 
		cout << "Parent Proc: " << gval << "\t" << lval << endl;


	return 0;
}
