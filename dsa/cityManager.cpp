#include "CityManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

void CityManager::addCities() {
    int count;
    std::cout << "Enter number of cities to add: ";
    std::cin >> count;

    std::ifstream infile("cities.txt");
    std::string line;
    int lastIndex = 0;
    while (getline(infile, line)) {
        lastIndex++;
    }
    infile.close();

    std::ofstream outfile("cities.txt", std::ios::app);
    std::string cityName;
    for (int i = 1; i <= count; i++) {
        std::cout << "Enter name for city " << lastIndex + i << ": ";
        std::cin >> cityName;
        outfile << (lastIndex + i) << ": " << cityName << "\n";
    }
    outfile.close();
}
