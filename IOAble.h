//Name:-Amritpal Singh
//Student ID : -150143196
//Email : -asingh882@myseneca.ca

#ifndef SDDS_IOABLE_H_
#define SDDS_IOABLE_H_

#include <iostream>

namespace sdds {
	class IOAble {

	public:
		IOAble(){}
		virtual std::ostream& csvWrite(std::ostream& ofstr)const = 0;
		virtual std::istream& csvRead(std::istream& ifstr) = 0;
		virtual std::ostream& write(std::ostream& ostr)const = 0;
		virtual std::istream& read(std::istream& istr) = 0;
		virtual ~IOAble(){}

	};

	std::ostream& operator<<(std::ostream& otr, IOAble&);
	std::istream& operator>>(std::istream& itr, IOAble&);


}

#endif