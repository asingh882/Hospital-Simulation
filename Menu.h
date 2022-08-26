#ifndef MENU_H
#define MENU_H

namespace sdds {
    class Menu {
        char* m_text = nullptr; // holds the menu content dynamically
        int m_noOfSel = 0;  // holds the number of options displayed in menu content
        void display()const;
    public:
        Menu();
        Menu(const char* MenuContent, int NoOfSelections);
        virtual ~Menu();

        int& operator>>(int& Selection);
        // add safe copying logic
    };

}

#endif