// Name: Artom Zabihi
// Seneca Student ID: azabihi1
// Seneca email: azabihi1@myseneca.ca
// Date of completion: December 2nd, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds {
    size_t Station::m_widthField = 0u;
    size_t Station::id_generator = 0u;
    char Utilities::m_delimiter = ',';

    Station::Station(const std::string &str) {
        Utilities util;
        bool more = true;
        size_t next_pos = 0;

        m_id = ++id_generator;
        m_name = util.extractToken(str, next_pos, more);
        if (m_widthField < util.getFieldWidth()) m_widthField = util.getFieldWidth();
        m_serial = stoi(util.extractToken(str, next_pos, more));
        m_quantity = stoi(util.extractToken(str, next_pos, more));
        m_desc = util.extractToken(str, next_pos, more);

    }

    const std::string &Station::getItemName() const {
        return m_name;
    }

    size_t Station::getNextSerialNumber() {
        return m_serial++;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    void Station::updateQuantity() {
        if (m_quantity > 0) m_quantity--;
    }

    void Station::display(std::ostream &os, bool full) const {
        os << std::setw(3) << std::setfill('0') << std::right << m_id << " | ";
        os << std::setw(m_widthField) << std::left << std::setfill(' ') << m_name << "| ";
        os << std::setw(6) << std::setfill('0') << std::right << m_serial << " | ";

        if (full){
            os << std::setw(4) << std::setfill(' ') << std::right << m_quantity << " | ";
            os << std::left << std::setfill(' ') << m_desc;
        }
        os << std::endl;
    }


} // sdds