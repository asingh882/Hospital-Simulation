//Name:- Amritpal Singh
//Student ID :- 150143196
//Email :- asingh882@myseneca.ca

#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_

#include <iostream>
#include "IOAble.h"
#include "Ticket.h"
#include "Time.h"

namespace sdds {
	class Patient: public IOAble {
		Ticket m_ticket;
		char* m_patientName = nullptr;
		int m_ohip = 0;
		bool m_fileIO;
	public:
		Patient(int ticketnumber = 0, bool fileIO = true);
		~Patient();
		virtual char type()const = 0;
		bool operator==(char c)const;
		bool operator==(const Patient& patient)const;
		operator Time()const;
		void fileIO(bool flag);
		bool fileIO()const;
		int number()const;
		void setArrivalTime();
		std::ostream& csvWrite(std::ostream& ostr)const;
		std::istream& csvRead(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);

	};
}

#endif