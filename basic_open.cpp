#include <iostream>
#include <cstring>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::ofstream;

int main()
{
	ofstream file;
 	file.open("text.txt");
	file << "Hello World!\n";
	file.close();

	return 0;
}
