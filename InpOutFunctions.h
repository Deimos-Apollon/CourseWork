//
// Created by deimos on 24.04.2021.
//

#ifndef COURSEWORK_INPOUTFUNCTIONS_H
#define COURSEWORK_INPOUTFUNCTIONS_H

#include "Bus.h"

Cities* ReadCities(std::ifstream& f);
Buses_names* ReadNames(std::ifstream& f);
Buses_types* ReadType(std::ifstream& f);

bool Check_file_corr(std::ifstream &f);
bool Check_file_corr(std::ofstream &f);

#endif //COURSEWORK_INPOUTFUNCTIONS_H
