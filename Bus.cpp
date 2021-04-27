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

void Bus::PrintList(std::ofstream& f)
{
    bus_name->GetName()->PrintList(f);
    f << "\n";
    bus_type->GetName()->PrintList(f);
    f << "\n";
    city->GetName()->PrintList(f);
    f << "\n";
    f << hour << ":" << min << "\n";
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
