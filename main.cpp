
#include "InpOutFunctions.h"
//иерархический список
#include <iomanip>

int main() {

    ////////// Opening files and checking if they are correct

    std::ofstream f_out("output.txt");
    if ( !Check_file_corr(f_out) ) {
        return -1;
    }

    std::ifstream f_in_names("input_buses_names.txt");
    std::ifstream f_in_types("input_buses_types.txt");
    std::ifstream f_in_cities("input_cities.txt");
    f_in_names >> std::resetiosflags(std::ios::skipws);
    f_in_types >> std::resetiosflags(std::ios::skipws);
    f_in_cities >> std::resetiosflags(std::ios::skipws);

    if ( !Check_file_corr(f_in_names) ) {
        f_out << "Error opening input_types file or it is empty\n";
        return -1;
    }
    if ( !Check_file_corr(f_in_names) ) {
        f_out << "Error opening input_types file or it is empty\n";
        return -1;
    }
    if ( !Check_file_corr(f_in_names) ) {
        f_out << "Error opening input_types file or it is empty\n";
        return -1;
    }

    //////////////////////////////////////////

    ////////////////Reading Additional classes

    Cities* cities = ReadCities(f_in_cities);
    cities->PrintList(f_out);

    Buses_names* names = ReadNames(f_in_names);
    names->PrintList(f_out);

    Buses_types* types = ReadType(f_in_types);
    types->PrintList(f_out);
    //////////////////////////////////////////

    ////////////////
    Bus bus;
    return 0;
}
