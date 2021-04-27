//
// Created by deimos on 24.04.2021.
//
#include "InpOutFunctions.h"

void ReadRequests(std::ifstream& f, std::ofstream& f_out,Buses_names* head_names, Buses_types* head_types, Cities* head_cities, List_Of_Buses* buses)
{
    while (!f.eof()) {
        unsigned short i = 0;
        unsigned params[5];
        for (unsigned int &param : params) param = 0;
        char c = ' ';
        bool corr = true;

        // чтение имени


            f >> c;
            if (c == '"') {
                String *line = new String;
                c = ' ';

                while (c != '"') {
                    char *tmpS = new char[N];
                    for (int k = 0; k < N; k++) {

                        f >> c;
                        if (c == '\n' || f.eof()) { corr = false; break; }

                        if (c == '"') {
                            if (k != 0) {

                                char *tmp2 = new char[k];
                                for (int j = 0; j < k; j++) {
                                    tmp2[j] = tmpS[j];
                                }

                                line->AddLastEl(tmp2);
                                line->SetLastElLength(k);
                                break;
                            }
                        }
                        tmpS[k] = c;
                    }
                    line->AddLastEl(tmpS);
                    line->SetLastElLength(N);

                    if (c == '\n' || f.eof()) {
                        corr = false;
                        break;
                    }
                }
            } else { corr = false; break; }


        //////////// чтение остальных параметров



        if (corr) {

                while (c != '\n' && corr) {
                    f >> c;
                    if (f.eof()) break;
                    switch (c) {
                        case '-':
                            if (i < 4) i++;
                            else corr = false;
                            break;
                        case '0':
                            params[i] = params[i] * 10 + 0;
                            break;
                        case '1':
                            params[i] = params[i] * 10 + 1;
                            break;
                        case '2':
                            params[i] = params[i] * 10 + 2;
                            break;
                        case '3':
                            params[i] = params[i] * 10 + 3;
                            break;
                        case '4':
                            params[i] = params[i] * 10 + 4;
                            break;
                        case '5':
                            params[i] = params[i] * 10 + 5;
                            break;
                        case '6':
                            params[i] = params[i] * 10 + 6;
                            break;
                        case '7':
                            params[i] = params[i] * 10 + 7;
                            break;
                        case '8':
                            params[i] = params[i] * 10 + 8;
                            break;
                        case '9':
                            params[i] = params[i] * 10 + 9;
                            break;

                        case ' ':
                            while (c == ' ') {
                                f >> c;
                                if (f.eof()) break;
                            }

                            f.seekg(-1, std::ios::cur);
                        case ':':
                            if (i < 4) i++;
                            else corr = false;
                            break;
                        case '\n':
                            break;
                        default:
                            corr = false;
                    }

                }
            }

        ProcessRequests(f_out, head_names, head_types, head_cities, buses,
                        params[0], params[1], params[2], params[3], params[4]);
    }
}

List_Of_Buses* ReadBuses(std::ifstream& f, Buses_names* head_names, Buses_types* head_types, Cities* head_cities)
{
    Bus* tmp_bus = new Bus;
    List_Of_Buses* tmp_list = new List_Of_Buses;

    while (!f.eof())
    {
        unsigned params[5];
        for (unsigned int & param : params) param = 0;
        unsigned short i = 0;
        char c = ' '; bool corr = true;


        while (c != '\n' && corr) {

            f >> c;
            if (f.eof()) break;
            switch(c)
            {
                case '0':
                    params[i] = params[i] * 10 + 0; break;
                case '1':
                    params[i] = params[i] * 10 + 1; break;
                case '2':
                    params[i] = params[i] * 10 + 2; break;
                case '3':
                    params[i] = params[i] * 10 + 3; break;
                case '4':
                    params[i] = params[i] * 10 + 4; break;
                case '5':
                    params[i] = params[i] * 10 + 5; break;
                case '6':
                    params[i] = params[i] * 10 + 6; break;
                case '7':
                    params[i] = params[i] * 10 + 7; break;
                case '8':
                    params[i] = params[i] * 10 + 8; break;
                case '9':
                    params[i] = params[i] * 10 + 9; break;

                case ' ':
                    while (c == ' '){
                        f >> c;
                        if (f.eof()) break;
                    }

                    f.seekg(-1, std::ios::cur);
                case ':':
                    if (i < 4) i++;
                    else corr = false;
                    break;
                case '\n':
                    break;
                default:
                    corr = false;
            }

        }

        if (i != 4) corr = false;

        if (corr)
        {
            Buses_names* tmp_names = head_names;
            Buses_types* tmp_types = head_types;
            Cities* tmp_cities = head_cities;

            for (int j = 0; j < params[0]; j++)
            {
                tmp_names = tmp_names->GetNext();
                if (tmp_names == nullptr) break;
            }

            for (int j = 0; j < params[1]; j++)
            {
                tmp_types = tmp_types->GetNext();
                if (tmp_types == nullptr) break;
            }

            for (int j = 0; j < params[2]; j++)
            {
                if (tmp_cities->GetNext() == nullptr) break;
                tmp_cities = tmp_cities->GetNext();
            }

            if (tmp_names != nullptr && tmp_types != nullptr && tmp_cities != nullptr) {
                if (tmp_list->GetHead() == nullptr) {
                    tmp_list->SetHead(tmp_bus);
                    tmp_bus->BusInitialize(tmp_names, tmp_types, tmp_cities, params[3], params[4]); //TODO проверка времени
                }
                else {
                    tmp_bus->SetNext(new Bus);
                    tmp_bus = tmp_bus->GetNext();
                    tmp_bus->BusInitialize(tmp_names, tmp_types, tmp_cities, params[3], params[4]);
                }
            }                     //TODO подробный отчёт по заявке и ошибки в формировании автобуса
        }
    }

    tmp_list->SetLast(tmp_bus);

    return tmp_list;
}

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

Buses_names* ReadNames(std::ifstream& f)
{
    Buses_names* city = new Buses_names;
    Buses_names* head = city;
    city->SetName(ReadStr(f));

    while (!f.eof())
    {
        city->SetNext(new Buses_names);
        city = city->GetNext();
        city->SetName(ReadStr(f));
    }
    return head;
}

Buses_types* ReadType(std::ifstream& f)
{
    Buses_types* city = new Buses_types;
    Buses_types* head = city;
    city->SetName(ReadStr(f));

    while (!f.eof())
    {
        city->SetNext(new Buses_types);
        city = city->GetNext();
        city->SetName(ReadStr(f));
    }
    return head;
}

bool Check_file_corr(std::ifstream &f)
{
    return (f.is_open() && !f.bad() && !f.eof());
}

bool Check_file_corr(std::ofstream &f)
{
    return (f.is_open() && !f.bad());
}