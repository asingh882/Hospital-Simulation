//Name:-Amritpal Singh
//Student ID : -150143196
//Email : -asingh882@myseneca.ca

#ifndef SDDS_TICKET_H_
#define SDDS_TICKET_H_

#include "Time.h"
#include "IOAble.h"

namespace sdds {
   class Ticket:public IOAble{
      Time m_time;
      int m_number;
   public:
       char value[50];
       Ticket(int number);
      operator Time()const;
      int number()const;
      void resetTime();
      std::ostream& csvWrite(std::ostream& ostr)const;
      std::istream& csvRead(std::istream& istr);
      std::ostream& write(std::ostream& ostr)const;
      std::istream& read(std::istream& istr);
      ~Ticket() {};
   };
}
#endif // !SDDS_TICKET_H_
