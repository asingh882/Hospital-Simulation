//Name:-Amritpal Singh
//Student ID : -150143196
//Email : -asingh882@myseneca.ca

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds {
   bool debug = true;  // made global in utils.h
   int getTime() 
   {  
      int mins = -1;
      if (debug) {
         Time t(0);
         cout << "Enter current time: ";
         do {
            cin.clear();
            cin >> t;   // needs extraction operator overloaded for Time
            if (!cin) {
               cout << "Invlid time, try agian (HH:MM): ";
               cin.clear();
            }
            else {
               mins = int(t);
            }
            cin.ignore(1000, '\n');
         } while (mins < 0);
      }
      else {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         mins = lt.tm_hour * 60 + lt.tm_min;
      }
      return mins;
   }
   int getInt(const char* prompt)
   {
       string value;
       int digit = 0, ch = 0;
       unsigned i = 0;
       if (prompt != nullptr)
       {
           cout << prompt;
       }
       do
       {
           digit = 0;
           ch = 0;
           getline(cin, value);
           for (i = 0; i < value.length(); i++)
           {
               if (isdigit(value[i]))
               {
                   digit++;
               }
               else 
               {
                   ch++;
               }
           }
           if (isdigit(value[0]) && ch > 0)
           {
               cout << "Enter only an integer";
           }
           else if (ch > 0)
           {
               cout << "Bad integer value";
           }
           else
           {
               return stoi(value);
           }
           cout << ", try again: ";
       } while (ch > 0);
       return 0;
   }

   int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError)
   {
       string value;
       int digit = 0, ch = 0;
       unsigned i = 0;
       if (prompt != nullptr)
       {
           cout << prompt;
       }

       do
       {
           digit = 0;
           ch = 0;
           getline(cin, value);
           for (i = 0; i < value.length(); i++)
           {
               if (isdigit(value[i]) || value[i] == '-')
               {
                   digit++;
               }
               else {
                   ch++;
               }
           }
           if (isdigit(value[0]) && ch > 0)
           {
               cout << "Enter only an integer, try again: ";
           }
           else if (ch > 0)
           {
               cout << "Bad integer value, try again: ";
           }
           else
           {
               if (stoi(value) <= max && stoi(value) >= min)
               {
                   return stoi(value);
               }
               else
               {
                   if (errorMessage != nullptr)
                   {
                       if (showRangeAtError == false)
                       {
                           cout << errorMessage;
                       }
                       else
                       {
                           cout << errorMessage << "[" << min << "<= value <= " << max << "]: ";
                       }
                   }
               }
           }
           digit = 0;
       } while (digit == 0);
       return 0;
   }

   char* getcstr(const char* prompt, std::istream& istr, char delimiter)
   {
       string value;
       char* rValue;
       int i = 0;

       if (prompt != nullptr)
       {
           cout << prompt;
       }
       getline(cin, value);
       rValue = new char[value.length() + 2];

       for (i = 0; value[i] != '\0'; i++)
       {
           rValue[i] = value[i];
       }
       rValue[i] = delimiter;
       rValue[i + 1] = '\0';
       return rValue;
   }
}