// Name: Artom Zabihi
// Seneca Student ID: azabihi1
// Seneca email: azabihi1@myseneca.ca
// Date of completion: December 2nd, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Utilities.h"
#include <algorithm>

namespace sdds {
    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more) {
        std::string result;
        size_t pos = str.find(m_delimiter, next_pos);

        if (pos == next_pos){
            more = false;
            throw "ERROR";
        } else if (pos != std::string::npos){
            result = str.substr(next_pos, pos-next_pos);
            more = true;
        } else {
            result = str.substr(next_pos);
            more = false;
        }
        if (m_widthField < result.length()) setFieldWidth(result.length());
        next_pos = ++pos;

        return trim(result);
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }

    std::string trim(const std::string &str) {
        std::string result = str;

        auto start = str.find_first_not_of(" \t");
        if (start != std::string::npos) {
            result = result.substr(start);
        }

        auto end = result.find_last_not_of(" \t");
        if (end != std::string::npos) {
            result = result.substr(0, end + 1);
        }

        return result;
    }
} // sdds