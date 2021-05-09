//
// Created by deimos on 24.04.2021.
//
#include "InpOutFunctions.h"

void ProcessRequests(std::ofstream &f, Buses_names* head_names, Buses_types* head_types, Cities* head_cities, List_Of_Buses* buses,
                     String* clients_name,
                    unsigned n_name, unsigned n_type, unsigned n_city, unsigned hour,
                    unsigned min, unsigned amount_of_ticks, unsigned request_num)
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


    unsigned short num = 1;
    List_of_Matches* matches = new List_of_Matches;
    auto matches_head = matches;

    std::cout << "\n\nЗаявка #" << request_num << ", ";
    clients_name->PrintList();
    std::cout << ", поиск подходящих автобусов: \n\n";

    while (tmp != nullptr)
    {
        if ((tmp->GetName() == tmp_names || n_name == 0) &&
            (tmp->GetType() == tmp_types || n_type == 0) &&
            (tmp->GetCity() == tmp_cities || n_city == 0) &&
            tmp->GetHour() == hour && tmp->GetMin() == min)
        {
            std::cout << "Автобус #" << num<< "\n";
            tmp->PrintList();
            std:: cout << "\n";
            matches->setNext(new List_of_Matches);
            matches = matches->GetNext();
            matches->setBus(tmp);
            num++;
        }
        tmp = tmp->GetNext();
    }
    --num;

    /////////////////////////////////////выбор автобуса
    if (num != 0) {

        unsigned int ans = 0;
        bool read_ans_corr = false;
        while (!read_ans_corr) {
            std::cout << "Введите номер подходящего автобуса (0 - отмена заявки): ";
            read_ans_corr = true;
            char ans_str[12];
            std::cin.getline(ans_str, 12);
            unsigned length = 0;
            ans = 0;
            for (auto c: ans_str) {
                if (c == '\0') break;
                length++;
            }
            if (length > 10) {
                std::cout << "ERR: Слишком длинный номер автобуса, такого в списке нет.\n";
                read_ans_corr = false;
            } else {
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

            if (read_ans_corr && ans > num) {
                read_ans_corr = false;
                std::cout << "ERR: Слишком большой номер автобуса, такого в списке нет.\n";
            }
        }

        ////////////////////////////////////Обрабатываем заявку, создаём билеты

        if (ans != 0) {

            ///////////////проход до выбранного автобуса
            Bus *match_bus = matches_head->GoTo(ans - 1);

            /////////////////////покупка билетов
            f << "Заявка #" << request_num << " покупка билетов:\n";
            if (match_bus->Enough_Seats(amount_of_ticks)) {
                Tickets *l_ticks = match_bus->GetTickets();

                Ticket *tmp = new Ticket;

                tmp->setPerson_name(clients_name);
                tmp->Set_First_Seat(match_bus->Take_a_Seats(1));

                tmp->Set_Last_Seat(match_bus->Take_a_Seats(amount_of_ticks - 1));

                if (l_ticks != nullptr) {

                    l_ticks->GetLast()->SetNext(tmp);
                    l_ticks->setLast(tmp);
                } else {
                    l_ticks = new Tickets;
                    l_ticks->setHead(tmp);
                    l_ticks->setLast(tmp);

                    match_bus->SetTickets(l_ticks);
                }

                f << "Имя покупателя: ";
                tmp->Get_Person_name()->PrintList(f);
                if (amount_of_ticks != 1) {
                    f << "   | Места: " << tmp->Get_First_Seat();
                    f << " - " << tmp->Get_Last_Seat() << "\n";
                } else
                {
                    f << "   | Место: " << tmp->Get_First_Seat() << "\n";
                }
                f << "\n";
                f << "Автобус: \n";
                match_bus->PrintList(f);
                f << "\n";
            } else f << "Err: Нет столько мест на рейс!\n\n";

        }
    } else
    {
        std::cout << "Подходящих автобусов нет :(\n\n";
        f << "Заявка #" << request_num << " нет подходящих рейсов\n\n";
    }
}

void ReadRequests(std::ifstream& f, std::ofstream& f_out,Buses_names* head_names, Buses_types* head_types, Cities* head_cities, List_Of_Buses* buses)
{

    unsigned request_num = 1;
    while (!f.eof()) {

        unsigned params[6];
        for (unsigned int &param : params) param = 0;

        char c = ' ';
        bool corr = true;

        /////////////////////////// чтение имени

        f >> c;
        String *name = new String;
        if (c == '"') {
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

                            name->AddLastEl(tmp2);
                            name->SetLastElLength(k);
                            break;
                        }
                    }
                    tmpS[k] = c;
                }

                if (c != '"') {
                    name->AddLastEl(tmpS);
                    name->SetLastElLength(N);
                }

                if (c == '\n' || f.eof()) {
                    corr = false;
                    break;
                }
            }
        } else corr = false;

        //////////// чтение остальных параметров

        if (corr) {
            unsigned short i = 0;

            f >> c;
            if (c == ' ') {
                while (c == ' ') {
                    f >> c;
                    if (f.eof()) break;
                }
                f.seekg(-1, std::ios::cur);
            } else corr = false;
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
                            if (i < 5) i++; else corr = false;
                            break;
                        case ':':
                            if (i == 3) i++; else corr = false;
                            break;
                        case '\n':
                            break;
                        default:
                            corr = false;
                    }

                }
        }
        if (params[5] == 0)
        {
            corr = false;
        }
        if (corr) ProcessRequests(f_out, head_names, head_types, head_cities, buses, name,
                        params[0], params[1], params[2], params[3], params[4], params[5], request_num);
        else f_out << "Заявка #" << request_num << " некорректна\n\n";
        request_num++;

        while (c != '\n' && !f.eof())
        {
            f >> c;
        }
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
    Buses_names* name = new Buses_names;
    Buses_names* head = name;
    name->SetName(ReadStr(f));

    while (!f.eof())
    {
        name->SetNext(new Buses_names);
        name = name->GetNext();
        name->SetName(ReadStr(f));
    }
    return head;
}

Buses_types* ReadType(std::ifstream& f)
{
    Buses_types* type = new Buses_types;
    Buses_types* head = type;

    unsigned i = 0;

    while (!f.eof()) {

        ++i;
        ///////////Reading bus type
        char c = ' ';
        bool corr = true;

        f >> c;
        String *name = new String;
        if (c == '"') {
            c = ' ';

            while (c != '"') {
                char *tmpS = new char[N];
                for (int k = 0; k < N; k++) {

                    f >> c;
                    if (c == '\n' || f.eof()) {
                        corr = false;
                        break;
                    }

                    if (c == '"') {
                        if (k != 0) {

                            char *tmp2 = new char[k];
                            for (int j = 0; j < k; j++) {
                                tmp2[j] = tmpS[j];
                            }

                            name->AddLastEl(tmp2);
                            name->SetLastElLength(k);
                            break;
                        }
                    }
                    tmpS[k] = c;
                }

                if (c != '"') {
                    name->AddLastEl(tmpS);
                    name->SetLastElLength(N);
                }

                if (c == '\n' || f.eof()) {
                    corr = false;
                    break;
                }
            }
        } else corr = false;

        unsigned int seats = 0;
        if (corr) {
            //////////////////Reading amount of seats
            f >> c;
            if (c == ' ') {
                while (c == ' ') {
                    f >> c;
                }
                f.seekg(-1, std::ios::cur);
            } else corr = false;

            while (corr) {

                f >> c;
                if ( c == '\n' || f.eof() ) break;
                if ('0' <= c && c <= '9') Char_to_int(c, seats);
                else {
                    corr = false; break;
                }
            }

        }

        if (corr){
            ////////////////Creating new element of bus_types

            type->SetName(name);
            type->SetSeats(seats);
            type->SetNext(new Buses_types);
            type = type->GetNext();
        }
        else std::cout << "Ошибка чтения типа автобуса #" << i << "\n\n";

        while (c != '\n' && !f.eof())
        {
            f >> c;
        }
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