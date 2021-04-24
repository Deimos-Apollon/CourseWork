//
// Created by InfinityDimas on 22.04.2021.
//

#include "Bus.h"
//Bus::Bus(Buses_names *m_bus_name, Buses_types *m_bus_type, Cities *m_city) {
//    bus_name = m_bus_name;
//    bus_type = m_bus_type;
//    city = m_city;
//}

void Bus::BusInitialize(Buses_names *m_bus_name, Buses_types *m_bus_type, Cities *m_city) {
    bus_name = m_bus_name;
    bus_type = m_bus_type;
    city = m_city;
}