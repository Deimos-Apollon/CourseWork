//
// Created by InfinityDimas on 23.04.2021.
//

#include "Additional_Classes.h"

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