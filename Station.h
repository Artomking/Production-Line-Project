// Name: Artom Zabihi
// Seneca Student ID: azabihi1
// Seneca email: azabihi1@myseneca.ca
// Date of completion: December 2nd, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <string>
namespace sdds {

    class Station {
        int m_id;
        std::string m_name;
        std::string m_desc;
        size_t m_serial;
        size_t m_quantity;

        static size_t m_widthField;
        static size_t id_generator;

    public:
        Station(const std::string&);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;

    };



} // sdds

#endif //SDDS_STATION_H
