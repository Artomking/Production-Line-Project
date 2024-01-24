// Name: Artom Zabihi
// Seneca Student ID: azabihi1
// Seneca email: azabihi1@myseneca.ca
// Date of completion: December 2nd, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

namespace sdds {
    LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations) {
        Utilities utils;
        std::string readLine;

        std::ifstream readFile(file);

        if (!readFile) {
            throw std::string("Unable to open file");
        }
        while (std::getline(readFile, readLine)) {
            Workstation *currentStation = nullptr, *nextStation = nullptr;
            bool more = false;
            size_t pos = 0;
            std::string stationName = utils.extractToken(readLine, pos, more);

            std::for_each(stations.begin(), stations.end(), [&](Workstation *workstation) {
                if (workstation->getItemName() == stationName) currentStation = workstation;
            });

            if (more) {
                stationName = utils.extractToken(readLine, pos, more);
                std::for_each(stations.begin(), stations.end(),
                              [&](Workstation *workstation) {
                                  if (workstation->getItemName() == stationName) nextStation = workstation;
                              });
            }
            currentStation->setNextStation(nextStation);
            m_activeLine.push_back(currentStation);
        }

        readFile.close();
        m_cntCustomerOrder = g_pending.size();

        Workstation *firstStation = nullptr;
        std::vector<Workstation *> activeLine = m_activeLine;

        auto tempStation = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws1){
            return !std::any_of(activeLine.begin(), activeLine.end(), [&](Workstation* ws2){
                return ws2->getNextStation() && ws2->getNextStation()->getItemName() == ws1->getItemName();
            });
        });

        if (tempStation != m_activeLine.end()){
            firstStation = *tempStation;
        }

        m_firstStation = firstStation;
    }

    void LineManager::reorderStations() {
        std::vector<Workstation *> activeLine;
        Workstation *workstation = m_firstStation;
        while (workstation != nullptr) {
            activeLine.push_back(workstation);
            workstation = workstation->getNextStation();
        }
        m_activeLine = activeLine;
    }

    bool LineManager::run(std::ostream &os) {
        static int iterationNumber = 0;

        os << "Line Manager Iteration: " << ++iterationNumber << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *workstation) {
            workstation->fill(os);
        });

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation *workstation) {
            workstation->attemptToMoveOrder();
        });

        if (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder) return true;

        return false;
    }

    void LineManager::display(std::ostream &os) const {
        for (const auto &station: m_activeLine) station->display(os);
    }
} // sdds