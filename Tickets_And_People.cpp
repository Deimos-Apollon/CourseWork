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
        std::cout << "    Место: " << tmp->Get_Seat();
        std::cout << "\n";
        tmp = tmp->Get_next();
    }
}

void Tickets::PrintList() {
    if (head != nullptr) head->PrintList();
    else std::cout << "ERR: список билетов пуст\n";
}