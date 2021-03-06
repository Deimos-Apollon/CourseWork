//
// Created by InfinityDimas on 22.04.2021.
//

#include "Bus.h"
//Bus::Bus(Buses_names *m_bus_name, Buses_types *m_bus_type, Cities *m_city) {
//    bus_name = m_bus_name;
//    bus_type = m_bus_type;
//    city = m_city;
//}


void Bus::BusInitialize(Buses_names *m_bus_name, Buses_types *m_bus_type, Cities *m_city, unsigned m_hour, unsigned m_min) {
    bus_name = m_bus_name;
    bus_type = m_bus_type;
    city = m_city;
    hour = m_hour;
    min = m_min;
    next = nullptr;
}



///////////////////////////////////////// output funcs
void Bus::PrintList(std::ofstream& f)
{
    if (bus_name->GetName() != nullptr &&
            bus_type->GetName() != nullptr &&
                city->GetName() != nullptr) {
        f << "Имя: ";
        bus_name->GetName()->PrintList(f);
        f << "\n";
        f << "Тип: ";
        bus_type->GetName()->PrintList(f);
        f << "     с количеством мест: " << bus_type->GetSeats();
        f << "\n";
        f << "Город следования:  ";
        city->GetName()->PrintList(f);
        f << "\n";
        f <<  "Отправление в ";
        f << hour << ":" << min << "\n";
    } else f << "Error\n";
}

void List_Of_Buses::PrintList(std::ofstream& f)
{
    Bus* tmp = m_head;
    while (tmp != nullptr)
    {
        f << "Автобус: \n";
        tmp->PrintList(f);
        tmp = tmp->GetNext();
        f << "\n";
    }
}

void Bus::PrintList()
{
    if (bus_name->GetName() != nullptr &&
        bus_type->GetName() != nullptr &&
        city->GetName() != nullptr) {
        std::cout << "Имя: ";
        bus_name->GetName()->PrintList();
        std::cout << "\n";
        std::cout << "Тип: "; bus_type->GetName()->PrintList();
        std::cout << "     с количеством мест: " << bus_type->GetSeats();
        std::cout << "\n";
        std::cout << "Город следования: ";
        city->GetName()->PrintList();
        std::cout << "\n";
        std::cout << "Отправление в ";
        std::cout << hour << ":" << min << "\n";
    } else std::cout << "Error\n";
}

void List_Of_Buses::PrintList()
{
    Bus* tmp = m_head;
    while (tmp != nullptr)
    {
        std::cout << "Автобус: \n";
        tmp->PrintList();
        tmp = tmp->GetNext();
        std::cout << "\n";
    }
}

void List_Of_Buses::Print_All_BusesTickets() {
    auto tmp = m_head; unsigned i = 1;
    while (tmp != nullptr)
    {
        if (tmp->GetTickets() != nullptr)
        {
            std::cout << "Билеты на рейс №" << i << ":\n";
            tmp->GetTickets()->PrintList();
        } else  std::cout << "Места на рейс №" << i << " все свободны\n";
        std::cout << "\n";
        tmp = tmp->GetNext();
        i++;
    }
}

Bus* List_of_Matches::GoTo(unsigned num)
{
    List_of_Matches* tmp = this->GetNext();
    unsigned i = 0;
    while (tmp!= nullptr && i < num)
    {
        tmp = tmp->GetNext();
        i++;
    }
    if (tmp == nullptr)
    {
        std::cout << "ERR: List_of_Matches\n";
        return nullptr;
    }
    else return tmp->GetBus();
}

unsigned Bus::Take_a_Seats(unsigned short amount) {
    taked_seats += amount;
    return taked_seats;
}

bool Bus::Enough_Seats(unsigned int num) {
    return (this->bus_type->GetSeats() >= num + taked_seats);
}