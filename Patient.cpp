//Name:- Amritpal Singh
//Student ID :- 150143196
//Email :- asingh882@myseneca.ca


#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include "Ticket.h"
#include "Patient.h"
#include "utils.h"

using namespace std;

namespace sdds {

	Patient::Patient(int ticketnumber, bool fileIO) :m_ticket(ticketnumber)
	{
		m_fileIO = fileIO;

	}
	
	Patient::operator Time()const
	{
		return m_ticket.operator Time();
	}

	Patient::~Patient()
	{
		delete[] m_patientName;
		m_patientName = nullptr;
	}

	bool Patient::operator==(char c)const
	{
		return type() == c;
	}

	bool Patient::operator==(const Patient& patient)const
	{
		return type() == patient.type();
	}
	
	void Patient::fileIO(bool flag)
	{
		m_fileIO = flag;
	}

	bool Patient::fileIO()const
	{
		return m_fileIO;
	}
	int Patient::number()const
	{
		return m_ticket.number();
	}

	void Patient::setArrivalTime()
	{
		m_ticket.resetTime();
	}

	ostream& Patient::csvWrite(ostream& ostr)const
	{
		ostr << type() << "," << m_patientName << "," << m_ohip << ",";
		m_ticket.csvWrite(ostr);
		return ostr;
	}
	istream& Patient::csvRead(istream& istr)
	{
		char name[1000];
		
		delete[] m_patientName;
		m_patientName = nullptr;
		istr.getline(name, 1000, ',');
		m_patientName = new char[strlen(name) + 1];
		strcpy(m_patientName, name);

		istr >> m_ohip;		

		istr.ignore();

		return istr >> m_ticket;

	}
	ostream& Patient::write(ostream& ostr)const
	{
		m_ticket.write(ostr);
		ostr << endl;
		ostr << m_patientName << ", OHIP: " << m_ohip;
		return ostr;
	}
	istream& Patient::read(istream& istr)
	{
		char name[1000];
		delete[] m_patientName;
		m_patientName = nullptr;
		cout << "Name: ";
		istr.getline(name, 1000);
		m_patientName = new char[strlen(name) + 1];
		strcpy(m_patientName, name);

		cout << "OHIP: ";
		m_ohip = getInt(100000000, 999999999, nullptr,"Invalid OHIP number, ");


		return istr;
	}

}