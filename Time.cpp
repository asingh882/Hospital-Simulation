//Name:-Amritpal Singh
//Student ID : -150143196
//Email : -asingh882@myseneca.ca

#include "Time.h"
#include "utils.h"
using namespace std;
namespace sdds {

	Time& Time::setToNow()
	{

		m_min = getTime();
		return *this;
	}

	Time::Time(unsigned int min)
	{
		m_min = min;
	}

	std::ostream& Time::write(std::ostream& ostr) const
	{
		int hours;
		int min;

		hours = m_min / 60;
		min = m_min % 60;

		if (hours < 10)
		{
			ostr << "0" << hours << ":";
		}
		else
		{
			ostr << hours << ":";
		}
		if(min < 10)
		{
			ostr << "0" << min;
		}
		else
		{
			ostr << min;
		}
		return ostr;

	}

	std::istream& Time::read(std::istream& istr)
	{
		int hours = 0, minutes = 0;
		char ch = ' ';
		istr >> hours >> ch >> minutes;
		if (hours < 0 || minutes < 0 || ch != ':')
		{
			istr.setstate(ios::failbit);
		}
		else
		{
			m_min = (hours * 60) + minutes;
		}
		
		return istr;
	}

	Time& Time::operator-=(const Time& D)
	{
		int hours1, hours2, resultedHours;
		int minutes1, minutes2, resultedMinutes;

		hours1 = m_min / 60;
		minutes1 = m_min % 60;

		hours2 = D.m_min / 60;
		minutes2 = D.m_min % 60;


		if (hours2 > hours1)
		{
			resultedHours = hours2 / 24;
			resultedHours = (hours1 + 24 * (resultedHours + 1)) - hours2;
		}
		else
		{
			resultedHours = hours1 - hours2;
		}
		
		if (minutes2 > minutes1)
		{
			resultedMinutes = (minutes2 + 60) - minutes1;
			resultedHours -= 1;
		}
		else
		{
			resultedMinutes = minutes1 - minutes2;
		}
		m_min = (resultedHours * 60) + resultedMinutes;
		return *this;
	}

	Time Time::operator-(const Time& D)const
	{
		Time time;

		int hours1, hours2, resultedHours;
		int minutes1, minutes2, resultedMinutes;

		hours1 = m_min / 60;
		minutes1 = m_min % 60;

		hours2 = D.m_min / 60;
		minutes2 = D.m_min % 60;

		if (hours2 > hours1)
		{
			resultedHours = hours2 / 24;
			resultedHours = (hours1 + 24*(resultedHours + 1)) - hours2;
		}
		else
		{
			resultedHours = hours1 - hours2;
		}

		if (minutes2 > minutes1)
		{
			resultedMinutes = (minutes2 + 60) - minutes1;
			resultedHours -= 1;
		}
		else
		{
			resultedMinutes = minutes1 - minutes2;
		}
		time.m_min = (resultedHours * 60) + resultedMinutes;
		
		return time;

	}

	Time& Time::operator+=(const Time& D)
	{
		m_min += D.m_min;
		
		return *this;
	}

	Time Time::operator+(const Time& D)const
	{
		Time time;

		time.m_min = m_min + D.m_min;

		return time;

	}

	Time& Time::operator=(unsigned int val)
	{
		m_min = val;
		return *this;

	}

	Time& Time::operator *= (unsigned int val)
	{
		m_min *= val;
		return *this;

	}

	Time& Time::operator /= (unsigned int val)
	{
		m_min /= val;
		return *this;

	}

	Time Time::operator *(unsigned int val)const
	{
		Time time;
		time.m_min = m_min * val;
		return time;

	}

	Time Time::operator /(unsigned int val)const
	{
		Time time;
		time.m_min = m_min / val;
		return time;
	}

	Time::operator unsigned int()const
	{
		return (unsigned)m_min;
	}

	Time::operator int()const
	{
		return (int)m_min;
	}

	std::ostream& operator<<(std::ostream& ostr, const Time& D)
	{
		return D.write(ostr);
	}

	std::istream& operator>>(std::istream& istr, Time& D)
	{
		return D.read(istr);
	}
}