#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include "PreTriage.h"
#include "utils.h"
#include "CovidPatient.h"
#include "TriagePatient.h"
#include "Patient.h"

using namespace std;

namespace sdds {

	PreTriage::PreTriage(const char* dataFilename) : m_averCovidWait(15), m_averTriageWait(5), m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2), m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2)
	{
		delete[] m_dataFilename;
		m_dataFilename = nullptr;
		m_dataFilename = new char[strlen(dataFilename) + 1];
		strcpy(m_dataFilename, dataFilename);
		load();
	}

	PreTriage::~PreTriage()
	{
		ofstream fout(m_dataFilename);
		ifstream fin(m_dataFilename);
		cout << "Saving Average Wait Times," << endl;
		cout << "   COVID Test: " << m_averCovidWait << endl;
		cout << "   Triage: " << m_averTriageWait << endl;
		cout << "Saving m_lineup..." << endl;
		fout << m_averCovidWait << "," << m_averTriageWait << endl;
		for (int i = 0; i < m_lineupSize; i++)
		{
			m_lineup[i]->fileIO(true);
			fout << *m_lineup[i] << endl;
			cout << i + 1 << "- " << *m_lineup[i] << endl;
		}
		cout << "done!" << endl;
		for (int i = 0; i < m_lineupSize; i++)
		{
			delete m_lineup[i];
			m_lineup[i] = nullptr;
		}
		delete[] m_dataFilename;
		m_dataFilename = nullptr;
	}

	const Time PreTriage::getWaitTime(const Patient& p)
	{
		int lineupSize = 0;
		int index;
		if (p.type() == 'C')
		{
			index = indexOfFirstInLine(p.type());
			if (index >= 0)
				lineupSize = m_lineup[index]->number() - p.number();
			return m_averCovidWait * (unsigned)lineupSize;
		}
		else
		{
			index = indexOfFirstInLine(p.type());
			if (index >= 0)
				lineupSize = m_lineup[index]->number() - p.number();
			return m_averTriageWait * (unsigned)lineupSize;
		}
	}


	void PreTriage::setAverageWaitTime(const Patient& p)
	{
		Time CT;
		CT.setToNow();
		if (p.type() == 'C')
		{
			m_averCovidWait = ((CT - p.operator Time()) + (m_averCovidWait * (unsigned)(p.number() - 1))) / (unsigned)p.number();

		}
		else if(p.type() == 'T')
		{
			m_averTriageWait = ((CT - p.operator Time()) + (m_averTriageWait * (unsigned)(p.number() - 1))) / (unsigned)p.number();

		}
	}

	void PreTriage::removePatientFromLineup(int index)
	{
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}

	int PreTriage::indexOfFirstInLine(char type) const
	{
		int i = 0;
		int flag = -1;
		for (i = 0; i < m_lineupSize && flag == -1; i++) 
		{
			if (*m_lineup[i] == type)
			{
				flag = i;
			}
		}
		return flag;
	}

	void PreTriage::load()
	{
		ifstream fin;
		int i = 0;
		char type[10];
		cout << "Loading data..." << endl;
		fin.open(m_dataFilename);
		fin >> m_averCovidWait;
		fin.ignore(1000, ',');
		fin >> m_averTriageWait;
		fin.ignore(1000, '\n');
		while (fin.getline(type, 1000, ',') && m_lineupSize < maxNoOfPatients)
		{
			
			if (type[0] == 'C')
				m_lineup[i] = new CovidPatient();
			else 
				m_lineup[i] = new TriagePatient();
			if (m_lineup[i])
			{
				m_lineup[i]->fileIO(true);
				fin >> *m_lineup[i];
				m_lineup[i]->fileIO(false);
				//m_lineup[i] = patient;
			}
			i++;
			m_lineupSize++;
		}
		if (i >= maxNoOfPatients)
		{
			cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
		}
		if (i == 0)
		{
			cout << "No data or bad data file!" << endl;
		}
		else
		{
			cout << i << " Records imported..." << endl;
		}
	}

	void PreTriage::reg()
	{
		int selection;
		if (m_lineupSize >= maxNoOfPatients)
		{
			cout << "Line up full!" << endl;
		}
		else
		{
			if (m_pMenu >> selection && m_lineupSize < maxNoOfPatients)
			{
				if (selection == 1)
					m_lineup[m_lineupSize] = new CovidPatient();
				else if (selection == 2)
					m_lineup[m_lineupSize] = new TriagePatient();
				if (m_lineup[m_lineupSize])
				{
					m_lineup[m_lineupSize]->setArrivalTime();
					cout << "Please enter patient information: " << endl;
					m_lineup[m_lineupSize]->fileIO(false);
					cin >> *m_lineup[m_lineupSize];
					cout << endl;
					cout << "******************************************" << endl;
					cout << *m_lineup[m_lineupSize];
					cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[m_lineupSize]) << endl;
					cout << "******************************************" << endl << endl;
					//m_lineup[m_lineupSize] = patient;
					m_lineupSize++;
				}
			}
		}
		
	}

	void PreTriage::admit()
	{
		int selection;
		int index = -1;
		if (m_pMenu >> selection)
		{
			if (selection == 1)
				index = indexOfFirstInLine('C');
			else if (selection == 2)
				index = indexOfFirstInLine('T');
			cout << endl;
			cout << "******************************************" << endl;
			if (index != -1 && index <= m_lineupSize)
			{
				m_lineup[index]->fileIO(false);
				cout << "Calling for ";
				cout << *m_lineup[index];
				cout << "******************************************" << endl << endl;
				setAverageWaitTime(*m_lineup[index]);
				removePatientFromLineup(index);
			}
		}
	}

	void PreTriage::run(void)
	{
		int selection;
		cout << endl;
		while (m_appMenu >> selection)
		{
			if (selection == 1)
			{
				reg();
			}
			else if (selection == 2)
			{
				admit();
			}
			else
			{
				break;
			}
		}
	}
}
