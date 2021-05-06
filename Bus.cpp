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
        bus_name->GetName()->PrintList(f);
        f << "\n";
        bus_type->GetName()->PrintList(f);
        f << "\n";
        city->GetName()->PrintList(f);
        f << "\n";
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
        bus_name->GetName()->PrintList();
        std::cout << "\n";
        bus_type->GetName()->PrintList();
        std::cout << "\n";
        city->GetName()->PrintList();
        std::cout << "\n";
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