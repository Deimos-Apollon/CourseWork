//
// Created by InfinityDimas on 23.04.2021.
//
#ifndef COURSEWORK_ADDITIONAL_CLASSES_H
#define COURSEWORK_ADDITIONAL_CLASSES_H
#include <fstream>

const unsigned N = 10;

class El_String{
    char* s = new char[N];
    El_String* next = nullptr;

public:
    char* GetS() { return s; }
    El_String* GetNext() { return next;}
    void SetS(char* m_s) { delete [] s; s = m_s; }
    void SetNext (El_String* m_next) { next = m_next; }

    void PrintList(std::ofstream& f);
};

class String{

    El_String *head = nullptr;
    El_String *last = nullptr;
    unsigned int Last_El_length = 0;

public:
    void AddLastEl(char* m_s);

    void SetHead(El_String* m_head) { head = m_head; }
    void SetLast(El_String* m_last) { last = m_last; }
    void SetLastElLength(unsigned int m_len) { Last_El_length = m_len; }
    unsigned int GetLastElLength() { return Last_El_length; }
    void PrintList(std::ofstream& f);

    El_String* GetHead() { return head; }
    El_String* GetLast() { return last; }
};

class Buses_names
{
    String name;
    Buses_names* next = nullptr;
public:
    String GetName() { return name; }
    Buses_names* GetNext() { return next; }
    void SetName(String m_name) { name = m_name; }
    void SetNext(Buses_names* m_next) { next = m_next; }
};


class Buses_types
{
    String name;
    Buses_types* next = nullptr;
public:
    String GetName() { return name; }
    Buses_types* GetNext() { return next; }
    void SetName(String m_name) { name = m_name; }
    void SetNext(Buses_types* m_next) { next = m_next; }
};

class Cities
{
    String* name;
    Cities* next = nullptr;
public:
    String* GetName() { return name; }
    Cities* GetNext() { return next; }
    void SetName(String* m_name) { name = m_name; }
    void SetNext(Cities* m_next) { next = m_next; }

    void PrintList(std::ofstream& f);
};

String* ReadStr(std::ifstream& f);

#endif //COURSEWORK_ADDITIONAL_CLASSES_H
