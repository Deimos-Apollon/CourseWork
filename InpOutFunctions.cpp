//
// Created by deimos on 24.04.2021.
//
#include "InpOutFunctions.h"

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

    std::cout << "\n\nЗаявка #" << request_num << ", Выберите один из подходящих автобусов: \n\n";

    unsigned short num = 1;
    while (tmp != nullptr)
    {
        if ((tmp->GetName() == tmp_names || n_name == 0) &&
            (tmp->GetType() == tmp_types || n_type == 0) &&
            (tmp->GetCity() == tmp_cities || n_city == 0) &&
            tmp->GetHour() == hour && tmp->GetMin() == min)
        {
            std::cout << "Автобус #" << num;
            std::cout << "\nИмя: "; tmp->GetName()->GetName()->PrintList();
            std::cout << "\nТип: "; tmp->GetType()->GetName()->PrintList();
            std::cout << "\nГород следования: "; tmp->GetCity()->GetName()->PrintList();
            std::cout << "\nОтправление в " << tmp->GetHour() << ":" << tmp->GetMin() << "\n\n";
            num++;
        }
        tmp = tmp->GetNext();
    }
    --num;


    unsigned int ans = 0;
    bool read_ans_corr = false;
    while (!read_ans_corr)
    {
        std::cout << "Введите номер подходящего автобуса: ";
        read_ans_corr = true;
        char ans_str[12];
        std::cin.getline(ans_str, 12);
        unsigned length = 0;
        ans = 0;
        for (auto c: ans_str)
        {
            if (c == '\0') break;
            length++;
        }
        if (length > 10)
        {
            std::cout << "ERR: Слишком длинный номер автобуса, такого в списке нет.\n";
            read_ans_corr = false;
        }
        else {
            for (auto c: ans_str) {
                if (c == '\0') break;
                if ('0' <= c && c <= '9') {
                    Char_to_int(c, ans);
                } else {
                    std::cout << "ERR: Некорректный номер автобуса\n";
                    read_ans_corr = false;
                    break;
                }
            }
        }

        if (read_ans_corr && ans == 0) {
            read_ans_corr = false;
            std::cout << "ERR: Нет автобуса под номером '0', нумерация с '1'\n";
        }

        if (read_ans_corr && ans > num) {
            read_ans_corr = false;
            std::cout << "ERR: Слишком большой номер автобуса, такого в списке нет.\n";
        }
    }

}

void ReadRequests(std::ifstream& f, std::ofstream& f_out,Buses_names* head_names, Buses_types* head_types, Cities* head_cities, List_Of_Buses* buses)
{

    unsigned request_num = 1;
    while (!f.eof()) {

        unsigned params[5];
        for (unsigned int &param : params) param = 0;

        char c = ' ';
        bool corr = true;

        /////////////////////////// чтение имени

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
            } else break;


        //////////// чтение остальных параметров


        if (corr) {
            unsigned short i = 0;

            f >> c;
            while (c == ' ') {
                f >> c;
                if (f.eof()) break;
            }
            f.seekg(-1, std::ios::cur);
                while (c != '\n' && corr) {
                    f >> c;
                    if (f.eof()) break;
                    if ('0' <= c && c <= '9') Char_to_int(c, params[i]);
                    else switch (c) {
                        case '-': break;
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
                        params[0], params[1], params[2], params[3], params[4], request_num);
        request_num++;
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
            if ('0' <= c && c <= '9') Char_to_int(c, params[i]);
            else
            switch(c)
            {
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

void Char_to_int(char c, unsigned int& number)
{
    switch(c)       //defualt case isn't needed, you must check if 0 <= c <= 9
    {
        case '0':
            number = number * 10 + 0;
            break;
        case '1':
            number = number * 10 + 1;
            break;
        case '2':
            number = number * 10 + 2;
            break;
        case '3':
            number = number * 10 + 3;
            break;
        case '4':
            number = number * 10 + 4;
            break;
        case '5':
            number = number * 10 + 5;
            break;
        case '6':
            number = number * 10 + 6;
            break;
        case '7':
            number = number * 10 + 7;
            break;
        case '8':
            number = number * 10 + 8;
            break;
        case '9':
            number = number * 10 + 9;
            break;
    }
}

bool Check_file_corr(std::ifstream &f)
{
    return (f.is_open() && !f.bad() && !f.eof());
}

bool Check_file_corr(std::ofstream &f)
{
    return (f.is_open() && !f.bad());
}