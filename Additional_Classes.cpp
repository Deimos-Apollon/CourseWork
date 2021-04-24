//
// Created by InfinityDimas on 23.04.2021.
//

#include "Additional_Classes.h"

//////////////////////// El_String methods

void El_String::PrintList(std::ofstream &f) {
    for (unsigned i = 0; i < N; i++)
    {
        f << s[i];
    }
}

void El_String::PrintLastEl(std::ofstream& f, unsigned len)
{
    for (unsigned i = 0; i < len; i++)
    {
        f << s[i];
    }
}

///////////////////////String's methods

String* ReadStr(std::ifstream& f)
{
    String* line = new String;
    char c = ' ';

    while (c != '\n' && !f.eof()) {
        char* tmpS = new char[N];
        for (int i = 0; i < N; i++) {
            f >> c;
            if (c == '\n' || f.eof()) {
                if (i != 0) {

                    char *tmp2 = new char[i];

                    for (int j = 0; j < i; j++) {
                        tmp2[j] = tmpS[j];
                    }

                    line->AddLastEl(tmp2);
                    line->SetLastElLength(i);
                }
                return line;
            }
            tmpS[i] = c;
        }
        line->AddLastEl(tmpS);
        line->SetLastElLength(N);
    }
    return line;
}

void String::AddLastEl(char* m_s)
{
    if (last != nullptr)
    {
        El_String* tmp = last;
        last = new El_String;
        last->SetS(m_s);  // SetNext не требуется, по умолчанию nullpt
        tmp->SetNext(last);
    } else if (head == nullptr)
    {
        head = new El_String;
        head->SetS(m_s);
        last = head;
    }
}

void String::PrintList(std::ofstream &f) {
    El_String* temp = this->GetHead();
    while (temp != last)
    {
        temp->PrintList(f);
        temp = temp->GetNext();
    }
    temp->PrintLastEl(f, Last_El_length);
}

///////////////////////////Buses_names methods

void Buses_names::PrintList(std::ofstream& f)
{
    f << "Вывод названий автобусов:\n";
    Buses_names* temp = this;
    unsigned int i = 1;
    while (temp != nullptr)
    {
        f << i << ": ";
        temp->GetName()->PrintList(f);
        temp = temp->GetNext();
        f << "\n";
        i++;
    }
    f << "\n";
}

///////////////////////////Buses_types methods

void Buses_types::PrintList(std::ofstream& f)
{
    f << "Вывод типов автобусов:\n";
    Buses_types* temp = this;
    unsigned int i = 1;
    while (temp != nullptr)
    {
        f << i << ": ";
        temp->GetName()->PrintList(f);
        temp = temp->GetNext();
        f << "\n";
        i++;
    }
    f << "\n";
}

///////////////////////////Cities' Methods

void Cities::PrintList(std::ofstream& f)
{
    f << "Вывод списка городов:\n";
    Cities* temp = this;
    unsigned int i = 1;
    while (temp != nullptr)
    {
        f << i << ": ";
        temp->GetName()->PrintList(f);
        temp = temp->GetNext();
        f << "\n";
        i++;
    }
    f << "\n";
}

//////////////////////////////////////////


