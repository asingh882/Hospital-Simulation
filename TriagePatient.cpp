#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "TriagePatient.h"
#include "Patient.h"

using namespace std;

namespace sdds {
   int nextTriageTicket = 1;


   TriagePatient::TriagePatient() :Patient(nextTriageTicket)
   {
	   nextTriageTicket++;
   }

   char TriagePatient::type()const
   {
	   return 'T';
   }

   std::istream& TriagePatient::csvRead(std::istream& istr)
   {
	   char symptoms[1000];
	   delete[] m_symptoms;
	   Patient::csvRead(istr);
	   istr.ignore(1000, ',');
	   istr.getline(symptoms, 1000, '\n');
	   m_symptoms = new char[strlen(symptoms) + 1];
	   strcpy(m_symptoms, symptoms);
	   nextTriageTicket = Patient::number() + 1;
	   return istr;
   }

   std::ostream& TriagePatient::csvWrite(std::ostream& ostr)const
   {
	   Patient::csvWrite(ostr);
	   ostr << "," << m_symptoms;
	   return ostr;

   }

   std::ostream& TriagePatient::write(std::ostream& ostr)const
   {
	   if (Patient::fileIO())
	   {
		   return csvWrite(ostr);
	   }
	   else
	   {
		   ostr << "TRIAGE" << endl;
		   Patient::write(ostr);
		   ostr << endl;
		   ostr << "Symptoms: " << m_symptoms << endl;
	   }
	   return ostr;

   }
   std::istream& TriagePatient::read(std::istream& istr)
   {
	   char symptoms[1000] = "\0";
	   if (Patient::fileIO())
	   {
		   return csvRead(istr);
	   }
	   else
	   {
		   delete[] m_symptoms;
		   Patient::read(istr);
		   cout << "Symptoms: ";
		   istr.getline(symptoms, 1000, '\n');
		   m_symptoms = new char[strlen(symptoms) + 1];
		   strcpy(m_symptoms, symptoms);
	   }
	   return istr;
   }
   TriagePatient::~TriagePatient()
   {
	   delete[] m_symptoms;
	   m_symptoms = nullptr;
   }

}