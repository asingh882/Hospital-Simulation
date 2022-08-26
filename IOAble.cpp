//Name:-Amritpal Singh
//Student ID :- 150143196
//Email :- asingh882@myseneca.ca

#include <iostream>
#include "IOAble.h"


using namespace std;

namespace sdds
{
	std::ostream& operator<<(std::ostream& otr, IOAble& able)
	{

		able.write(otr);
		return otr;

	}

	std::istream& operator>>(std::istream& itr, IOAble& able)
	{
		able.read(itr);
		return itr;

	}

}