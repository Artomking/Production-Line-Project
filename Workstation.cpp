// Name: Artom Zabihi
// Seneca Student ID: azabihi1
// Seneca email: azabihi1@myseneca.ca
// Date of completion: December 2nd, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"

#include <ostream>

namespace sdds {

    std::deque<CustomerOrder> g_pending = {};
    std::deque<CustomerOrder> g_completed = {};
    std::deque<CustomerOrder> g_incomplete = {};

    Workstation::Workstation(const std::string &str) : Station(str) {
        m_pNextStation = nullptr;
    }

    void Workstation::fill(std::ostream &os) {
        if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder() {
        if (m_orders.empty()) return false;

        if (m_orders.front().isItemFilled(getItemName()) || getQuantity() <= 0) {
            if (!m_pNextStation) {
                if (m_orders.front().isOrderFilled()) g_completed.push_back(std::move(m_orders.front()));
                else g_incomplete.push_back((std::move(m_orders.front())));
            } else *m_pNextStation += std::move(m_orders.front());
            m_orders.pop_front();
            return true;
        }

        return false;
    }

    void Workstation::setNextStation(Workstation *station) {
        m_pNextStation = station;
    }

    void Workstation::display(std::ostream &os) const {
        if (m_pNextStation) os << Station::getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
        else os << Station::getItemName() << " --> End of Line" << std::endl;
    }

    Workstation &Workstation::operator+=(CustomerOrder &&newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }

    Workstation *Workstation::getNextStation() const {
        return m_pNextStation;
    }
} // sdds