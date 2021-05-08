//
// Created by deimos on 06.05.2021.
//

#include "Tickets_And_People.h"

void Ticket::PrintList() {   ///////////TODO Спросить про наследование
    Ticket* tmp = this;
    while (tmp != nullptr)
    {
        std::cout << "Имя: ";
        tmp->Get_Person_name()->PrintList();
        if (tmp->Get_First_Seat() != tmp->Get_Last_Seat()) {
            std::cout << "    Места: " << tmp->Get_First_Seat()
                      << " - " << tmp->Get_Last_Seat();
        }else std::cout << "    Место: " << tmp->Get_First_Seat();
        std::cout << "\n";
        tmp = tmp->Get_next();
    }
}

void Tickets::PrintList() {
    if (head != nullptr) head->PrintList();
}