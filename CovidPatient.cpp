#include <iostream>
#include "CovidPatient.h"
#include "Patient.h"

using namespace std;

namespace sdds {
   int nextCovidTicket = 1;

   CovidPatient::CovidPatient():Patient(nextCovidTicket)
   {
	   nextCovidTicket++;
   }

   char CovidPatient::type()const
   {
	   return 'C';
   }

   std::istream& CovidPatient::csvRead(std::istream& istr)
   {
		Patient::csvRead(istr);
		nextCovidTicket = Patient::number() ;
		istr.ignore(1000, '\n');
		return istr;
   }

   std::ostream& CovidPatient::csvWrite(std::ostream& ostr)const
   {

	   Patient::csvWrite(ostr);
	   return ostr;
   }
   
   std::ostream& CovidPatient::write(std::ostream& ostr)const
   {
	   if (Patient::fileIO())
	   {
			return csvWrite(ostr);
	   }	
	   else
	   {
		   ostr << "COVID TEST" << endl;
		   Patient::write(ostr);
		   ostr << endl;
	   }
	   return ostr;

   }
   std::istream& CovidPatient::read(std::istream& istr)
   {
	   if (Patient::fileIO())
	   {
		   return csvRead(istr);
	   }
	   else
	   {
		   return Patient::read(istr);
	   }
   }



}