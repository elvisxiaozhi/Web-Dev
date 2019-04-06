#include <iostream>
#include <cstring>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

int main()
{
	ifstream file;
	string line;
	file.open("text.txt");
	while (getline(file, line)) {
		cout << line << endl;
	}
	file.close();

	return 0;
}
