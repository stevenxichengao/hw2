#include "util.h"

using namespace std;
int main(int argc, char* argv[])
{
	std::set<string>::iterator it;
	string s = "Great good";
	set<string> temp = parseStringToWords(s);
	for(it = temp.begin(); it != temp.end(); ++it){
		cout << *it << "\n";
	}
}