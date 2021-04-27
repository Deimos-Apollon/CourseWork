//
// Created by InfinityDimas on 22.04.2021.
//

#ifndef COURSEWORK_BUS_H
#define COURSEWORK_BUS_H
#include "Additional_Classes.h"

class Bus {
    Buses_names* bus_name;
    Buses_types* bus_type;
    Cities* city;
    //Seats* seats;

    unsigned hour, min;
    Bus* next;
public:
    //Bus (Buses_names* m_bus_name,
    //     Buses_types* m_bus_type,
    //     Cities* m_city);
    void Bus::BusInitialize(Buses_names *m_bus_name,
                            Buses_types *m_bus_type,
                            Cities *m_city,
                            unsigned m_hour, unsigned m_min);
    Bus* GetNext() { return next; }
    void SetNext(Bus* m_next) { next = m_next; }

    void PrintList(std::ofstream& f);
};


class List_Of_Buses{
    Bus* m_head;
    Bus* m_last;
public:
    void SetHead(Bus* head) { m_head = head; }
    void SetLast(Bus* last) { m_last = last; }
    Bus* GetHead() { return m_head; }

    void PrintList(std::ofstream& f);
};


Bus* Bus_create(unsigned name,
                unsigned type,
                unsigned city,
                unsigned hour,
                unsigned minute);


#endif //COURSEWORK_BUS_H
