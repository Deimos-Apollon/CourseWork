//
// Created by deimos on 24.04.2021.
//

#include "InpOutFunctions.h"

Cities* ReadCities(std::ifstream& f)
{
    Cities* city = new Cities;
    Cities* head = city;
    city->SetName(ReadStr(f));

    while (!f.eof())
    {
        city->SetNext(new Cities);
        city = city->GetNext();
        city->SetName(ReadStr(f));
    }
    return head;
}


bool Check_file_corr(std::ifstream &f)
{
    return (f.is_open() and !f.bad() and !f.eof());
}

bool Check_file_corr(std::ofstream &f)
{
    return (f.is_open() and !f.bad());
}