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


void ProcessRequests(std::ofstream &f, Buses_names* head_names, Buses_types* head_types, Cities* head_cities, List_Of_Buses* buses,
                     unsigned n_name, unsigned n_type, unsigned n_city, unsigned hour, unsigned min, unsigned request_num)
{
    Buses_names* tmp_names = head_names;
    Buses_types* tmp_types = head_types;
    Cities* tmp_cities = head_cities;

    //n_name = 0 - означет пропуск имени

    for (int j = 1; j <= n_name; j++)
    {
        tmp_names = tmp_names->GetNext();
        if (tmp_names == nullptr) break;
    }

    for (int j = 1; j <= n_type; j++)
    {
        tmp_types = tmp_types->GetNext();
        if (tmp_types == nullptr) break;
    }

    for (int j = 1; j <= n_city; j++)
    {
        if (tmp_cities->GetNext() == nullptr) break;
        tmp_cities = tmp_cities->GetNext();
    }

    Bus* tmp = buses->GetHead();
    while (tmp != nullptr)
    {
        if ((tmp->GetName() == tmp_names || n_name == 0) &&
                (tmp->GetType() == tmp_types || n_type == 0) &&
                (tmp->GetCity() == tmp_cities || n_city == 0) &&
                        tmp->GetHour() == hour && tmp->GetMin() == min)
        {
            f << "По заявке #" << request_num << " подходит автобус с параметрами: \nИмя: "; tmp->GetName()->GetName()->PrintList(f);
            f << "\nТип: "; tmp->GetType()->GetName()->PrintList(f);
            f << "\nГород следования: "; tmp->GetCity()->GetName()->PrintList(f);
            f << "\nОтправление в " << tmp->GetHour() << ":" << tmp->GetMin() << "\n\n";
        }
        tmp = tmp->GetNext();
    }

}