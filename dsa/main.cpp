#include <iostream>
#include <vector>
#include "CityManager.h"
#include "RoadManager.h"
#include "BudgetManager.h"

int main() {
    int choice;
    do {
        std::cout << "\n=== Road Budget Management System ===\n"
                  << "1. Add New City(ies)\n"
                  << "2. Add Roads Between Cities\n"
                  << "3. Add the Budget for Roads\n"
                  << "4. Edit City\n"
                  << "5. Search for a City Using Its Index\n"
                  << "6. Display Cities\n"
                  << "7. Display Roads\n"
                  << "8. Display Recorded Data on Console\n"
                  << "9. Exit\n"
                  << "Enter choice: ";
        std::cin >> choice;

        switch(choice) {
            case 1: CityManager::addCities(); break;
            case 2: RoadManager::addRoad(); break;
            case 3: BudgetManager::addBudget(); break;
            case 4: CityManager::editCity(); break;
            case 5: CityManager::searchCity(); break;
            case 6: CityManager::displayCities(); break;
            case 7: RoadManager::displayRoads(); break;
            case 8: BudgetManager::displayAll(); break;
            case 9: std::cout << "Exiting...\n"; break;
            default: std::cout << "Invalid choice.\n";
        }

    } while (choice != 9);

    return 0;
}
