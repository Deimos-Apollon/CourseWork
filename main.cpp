#include "InpOutFunctions.h"
//иерархический список
#include <iomanip>

std::ofstream f_out("output.txt");

int main() {

    ////////////////////////////////////////////////////////////////// Opening files and checking if they are correct


    if ( !Check_file_corr(f_out) ) {
        return -1;
    }

    std::ifstream f_in("input_requests.txt");
    std::ifstream f_in_names("input_buses_names.txt");
    std::ifstream f_in_types("input_buses_types.txt");
    std::ifstream f_in_cities("input_cities.txt");
    std::ifstream f_in_buses("input_buses.txt");

    f_in >> std::resetiosflags(std::ios::skipws);
    f_in_names >> std::resetiosflags(std::ios::skipws);
    f_in_types >> std::resetiosflags(std::ios::skipws);
    f_in_cities >> std::resetiosflags(std::ios::skipws);
    f_in_buses >> std::resetiosflags(std::ios::skipws);

    if ( !Check_file_corr(f_in) ) {
        f_out << "Error opening input_requests.txt file or it is empty\n";
        return -1;
    }
    if ( !Check_file_corr(f_in_names) ) {
        f_out << "Error opening input_buses_names.txt file or it is empty\n";
        return -1;
    }
    if ( !Check_file_corr(f_in_types) ) {
        f_out << "Error opening input_buses_types.txt file or it is empty\n";
        return -1;
    }
    if ( !Check_file_corr(f_in_cities) ) {
        f_out << "Error opening input_cities.txt file or it is empty\n";
        return -1;
    }
    if ( !Check_file_corr(f_in_buses) ) {
        f_out << "Error opening input_buses.txt file or it is empty\n";
        return -1;
    }


    ////////////////////////////////////////////////////////////////////////Reading Additional classes

    Cities* cities = ReadCities(f_in_cities);
    //cities->PrintList(f_out);

    Buses_names* names = ReadNames(f_in_names);
    //names->PrintList(f_out);

    Buses_types* types = ReadType(f_in_types);
    //types->PrintList(f_out);


    ////////////////////////////////////////////////////////////////////////Creating Buses' lists

    List_Of_Buses* buses = ReadBuses(f_in_buses, names, types, cities);
    //if (buses != nullptr) buses->PrintList(f_out);

    ///////////////////////////////////////////////////////////////////////Reading and Processing Requests
    ReadRequests(f_in, f_out, names, types, cities, buses);

    //TODO сделать несколько билетов для одного человека при вводе и список людей и его билетов + места

    return 0;
}
