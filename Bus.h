//
// Created by InfinityDimas on 22.04.2021.
//

#ifndef COURSEWORK_BUS_H
#define COURSEWORK_BUS_H
#include "Additional_Classes.h"
#include "Tickets_And_People.h"


class Bus {
    Buses_names* bus_name = nullptr;
    Buses_types* bus_type = nullptr;
    Cities* city = nullptr;
    unsigned hour = 0, min = 0;

    const unsigned all_seats = 50;
    unsigned taked_seats = 0;

    Tickets* tickets = nullptr;
    Bus* next = nullptr;
public:
    //Bus (Buses_names* m_bus_name,
    //     Buses_types* m_bus_type,
    //     Cities* m_city);
    void BusInitialize(Buses_names *m_bus_name,
                            Buses_types *m_bus_type,
                            Cities *m_city,
                            unsigned m_hour, unsigned m_min);
    Buses_names* GetName() { return bus_name; };
    Buses_types* GetType() { return bus_type; };
    Cities* GetCity() { return city; };
    Bus* GetNext() { return next; }
    unsigned GetHour() { return hour; }
    unsigned GetMin() { return min; }
    Tickets* GetTickets() {return tickets;}
    Tickets* SetTickets(Tickets* m_tickets) {tickets = m_tickets; }

    bool Enough_Seats(unsigned num);
    unsigned Take_a_Seats(unsigned short amount);
    void SetNext(Bus* m_next) { next = m_next; }
    void PrintList(std::ofstream& f);
    void PrintList();
};


class List_Of_Buses{
    Bus* m_head = nullptr;
    Bus* m_last = nullptr;
public:
    void SetHead(Bus* head) { m_head = head; }
    void SetLast(Bus* last) { m_last = last; }
    Bus* GetHead() { return m_head; }

    void PrintList(std::ofstream& f);
    void PrintList();
};

class List_of_Matches{
    Bus* bus = nullptr;
    List_of_Matches* next = nullptr;
public:
    void setBus(Bus* m_bus) {bus = m_bus; }
    void setNext(List_of_Matches* m_next) {next = m_next; }
    Bus* GetBus() {return bus; }
    List_of_Matches* GetNext() { return next; }
    Bus* GoTo(unsigned num);

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