// Name: Artom Zabihi
// Seneca Student ID: azabihi1
// Seneca email: azabihi1@myseneca.ca
// Date of completion: December 2nd, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <vector>
#include <ostream>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds {
    size_t CustomerOrder::m_widthField = 0u;

    CustomerOrder::CustomerOrder() {
        m_name = "";
        m_product = "";
        m_cntItem = 0;
        m_lstItem = nullptr;
    }

    CustomerOrder::CustomerOrder(const std::string &str)  : m_lstItem(nullptr){
        Utilities util;
        bool more = true;
        size_t next_pos = 0;
        std::vector<std::string> vector;

        if (m_widthField < util.getFieldWidth()) m_widthField = util.getFieldWidth();
        m_name = util.extractToken(str, next_pos, more);
        m_product = util.extractToken(str, next_pos, more);

        do {
            std::string temp = util.extractToken(str, next_pos, more);
            if (temp.length()!=0){
                vector.push_back(temp);
                m_cntItem++;
            }
        } while (more);

        m_lstItem = new Item*[m_cntItem];
        for (size_t i=0; i < m_cntItem; i++){
            m_lstItem[i] = new Item(vector[i]);
        }

        if (m_widthField < m_product.length()) m_widthField = m_product.length();
        if (m_widthField < util.getFieldWidth()) m_widthField = util.getFieldWidth();

    }

    CustomerOrder::CustomerOrder(const CustomerOrder &) {
        throw std::exception();
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&src) noexcept{
        m_lstItem = nullptr;
        *this = std::move(src);
    }

    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&src) noexcept{
        if (this != &src){
            for (size_t i = 0; i < m_cntItem; i++){
                delete m_lstItem[i];
                m_lstItem[i] = nullptr;
            }
            delete[] m_lstItem;
            m_lstItem = nullptr;

            m_name = src.m_name;
            src.m_name = "";

            m_cntItem = src.m_cntItem;
            src.m_cntItem = 0;

            m_product = src.m_product;
            src.m_product = "";

            m_lstItem = src.m_lstItem;
            src.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; i++){
            if (!m_lstItem[i]->m_isFilled) return false;
        }
        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string &itemName) const {
        for (size_t i = 0; i < m_cntItem; i++){
            if (!m_lstItem[i]->m_isFilled && m_lstItem[i]->m_itemName == itemName) return false;
        }
        return true;
    }

    void CustomerOrder::fillItem(Station &station, std::ostream &os) {
        int index = -1;

        for (size_t i = 0; i < m_cntItem && index == -1; i++){
            if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled){
                index = (int)i;
            }
        }
        if (index==-1) return;

        bool flag = false;
        for (size_t i = index; i < m_cntItem && !flag; i++){
            if (m_lstItem[i]->m_itemName == station.getItemName()){
                if (station.getQuantity() > 0){
                    station.updateQuantity();
                    m_lstItem[i]->m_isFilled = true;
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    flag = true;
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
                } else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream &os) const{
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++){
            os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] " << std::setw(m_widthField-1) <<
            std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << "- ";
            if (m_lstItem[i]->m_isFilled) os << "FILLED\n";
            else os << "TO BE FILLED\n";
        };
    }
} // sdds