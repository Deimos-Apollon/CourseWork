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
public:
    //Bus (Buses_names* m_bus_name,
    //     Buses_types* m_bus_type,
    //     Cities* m_city);
    void Bus::BusInitialize(Buses_names *m_bus_name,
                            Buses_types *m_bus_type,
                            Cities *m_city);
};


#endif //COURSEWORK_BUS_H
