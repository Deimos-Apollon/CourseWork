//
// Created by deimos on 06.05.2021.
//

#ifndef COURSEWORK_TICKETS_AND_PEOPLE_H
#define COURSEWORK_TICKETS_AND_PEOPLE_H
#include "Additional_Classes.h"

class Ticket{
    String* person_name;
    unsigned short first_seat = 0, last_seat = 0;
    Ticket* next = nullptr;
public:
    void setPerson_name(String* name) { person_name = name; }
    void SetNext(Ticket* m_next) { next = m_next; }
    void Set_First_Seat(unsigned short f_seat) { first_seat = f_seat; }
    void Set_Last_Seat( unsigned short l_seat) { last_seat = l_seat; }

    String* Get_Person_name() {return person_name; }
    unsigned short Get_First_Seat() { return first_seat; }
    unsigned short Get_Last_Seat() { return last_seat; }
    Ticket* Get_next() { return next; }

    void PrintList();
};

class Tickets
{
    Ticket* head = nullptr;
    Ticket* last = nullptr;
public:
    void setHead(Ticket* m_head) { head = m_head; }
    void setLast(Ticket* m_last) {last = m_last; }
    Ticket* getHead() { return head; }
    Ticket* GetLast() { return last; }

    void PrintList();
};


#endif //COURSEWORK_TICKETS_AND_PEOPLE_H
