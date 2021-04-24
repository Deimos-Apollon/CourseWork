
#include "InpOutFunctions.h"
//иерархический список


int main() {


    // Opening files and checking if they are correct
    std::ofstream f_out("output.txt");
    if ( !Check_file_corr(f_out) ) {
        return -1;
    }

    std::ifstream f_in_names("input_buses_names.txt");
    std::ifstream f_in_types("input_buses_types.txt");
    std::ifstream f_in_cities("input_cities.txt");
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

    //

    Bus bus;
    Cities* city = ReadCities(f_in_cities);
    city->PrintList(f_out);
    return 0;
}
