#include <iostream>
#include <cassert>
#include <fstream>
using namespace std;

class ArrayClass
{
public:
	ArrayClass();
	~ArrayClass();
	bool operator ==(const ArrayClass&);
	bool operator !=(const ArrayClass&);
	ArrayClass& operator = (const ArrayClass&);
};

int main()
{
	std::cout << "review cpp..." << std::endl;
	
	cout << "Run __FILE__:" << __FILE__ << " __LINE__:" << __LINE__ << " __DATE__:" << __DATE__ << " __TIME__:" << __TIME__ << endl;
	
	ofstream outfile("MakefileJ");
	if( !outfile )
	{
		cerr << "ofstream failed..." << endl;
	}
	assert(1);
	return 0;
}