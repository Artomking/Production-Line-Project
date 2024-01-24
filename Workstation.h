// Name: Artom Zabihi
// Seneca Student ID: azabihi1
// Seneca email: azabihi1@myseneca.ca
// Date of completion: December 2nd, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef FINALPROJECT_WORKSTATION_H
#define FINALPROJECT_WORKSTATION_H


#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds{
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station{
        std::deque<CustomerOrder> m_orders{};
        Workstation* m_pNextStation{nullptr};
    public:
        Workstation(const std::string&);
        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);
    };

} // sdds

#endif //FINALPROJECT_WORKSTATION_H
