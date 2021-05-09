//
// Created by deimos on 24.04.2021.
//

#ifndef COURSEWORK_INPOUTFUNCTIONS_H
#define COURSEWORK_INPOUTFUNCTIONS_H

#include "Bus.h"

Cities* ReadCities(std::ifstream& f);
Buses_names* ReadNames(std::ifstream& f);
Buses_types* ReadType(std::ifstream& f);
List_Of_Buses* ReadBuses(std::ifstream& f, Buses_names* head_names,
                         Buses_types* head_types, Cities* head_cities);
void ReadRequests(std::ifstream& f, std::ofstream& f_out,
                  Buses_names* head_names, Buses_types* head_types,
                  Cities* head_cities, List_Of_Buses* buses);



void ProcessRequests(std::ofstream &f, Buses_names* head_names, Buses_types* head_types, Cities* head_cities,
                     List_Of_Buses* buses, String* clients_name,
                     unsigned n_name, unsigned n_type,
                     unsigned n_city, unsigned hour, unsigned min, bool time_less, bool time_more, unsigned amount_tick,
                     unsigned request_num);


void Char_to_int(char c, unsigned int& number);
bool Check_file_corr(std::ifstream &f);
bool Check_file_corr(std::ofstream &f);

#endif //COURSEWORK_INPOUTFUNCTIONS_H
