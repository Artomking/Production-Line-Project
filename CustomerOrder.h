// Name: Artom Zabihi
// Seneca Student ID: azabihi1
// Seneca email: azabihi1@myseneca.ca
// Date of completion: December 2nd, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <string>
#include "Station.h"

namespace sdds {

    struct Item {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string&src) : m_itemName(src){};

        Item(){};
    };
    class CustomerOrder {
        std::string m_name{};
        std::string m_product{};
        size_t m_cntItem{0};
        Item** m_lstItem{nullptr};
        static size_t m_widthField;

    public:
        CustomerOrder();
        CustomerOrder(const std::string& str);

        CustomerOrder(const CustomerOrder&);
        CustomerOrder& operator=(const CustomerOrder&) = delete;

        CustomerOrder(CustomerOrder&&) noexcept;
        CustomerOrder& operator=(CustomerOrder&&) noexcept;

        ~CustomerOrder();

        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };

} // sdds

#endif //SDDS_CUSTOMERORDER_H
