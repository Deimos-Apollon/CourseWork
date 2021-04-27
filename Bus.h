//
// Created by InfinityDimas on 22.04.2021.
//

#ifndef COURSEWORK_BUS_H
#define COURSEWORK_BUS_H
#include "Additional_Classes.h"

class Bus {
    Buses_names* bus_name = nullptr;
    Buses_types* bus_type = nullptr;
    Cities* city = nullptr;
    //Seats* seats;

    unsigned hour, min;
    Bus* next = nullptr;
public:
    //Bus (Buses_names* m_bus_name,
    //     Buses_types* m_bus_type,
    //     Cities* m_city);
    void Bus::BusInitialize(Buses_names *m_bus_name,
                            Buses_types *m_bus_type,
                            Cities *m_city,
                            unsigned m_hour, unsigned m_min);
    Buses_names* GetName() { return bus_name; };
    Buses_types* GetType() { return bus_type; };
    Cities* GetCity() { return city; };
    Bus* GetNext() { return next; }
    unsigned GetHour() { return hour; }
    unsigned GetMin() { return min; }

    void SetNext(Bus* m_next) { next = m_next; }
    void PrintList(std::ofstream& f);
};


class List_Of_Buses{
    Bus* m_head = nullptr;
    Bus* m_last = nullptr;
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

void ProcessRequests(std::ofstream &f,
                     Buses_names* head_names, Buses_types* head_types, Cities* head_cities,
                     List_Of_Buses* buses,
                     unsigned n_name, unsigned n_type, unsigned n_city, unsigned hour, unsigned min, unsigned request_num);

#endif //COURSEWORK_BUS_H
