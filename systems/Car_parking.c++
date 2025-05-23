#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;

struct Park {
    string parking_code;
    string name;
    int available_space;
    string location;
    
    string toCSV() const {
        return parking_code + "," + name + "," + 
               to_string(available_space) + "," + location;
    }
    
    string description() const {
        return "Name: " + name + ", Location: " + location + 
               ", Available Spaces: " + to_string(available_space);
    }
};

struct Distance {
    string target;
    int distance;  // in meters
};

vector<Park> parks;
map<string, vector<Distance>> graph;

// Utility Functions
bool isNumber(const string& s) {
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

bool parkExists(const string& code) {
    return any_of(parks.begin(), parks.end(), 
        [&](const Park& p) { return p.parking_code == code; });
}

// Lambda function [&](const Park& p): Anonymous function to check each park
// [&]: Captures all variables by reference
// (const Park& p): Takes each park object as parameter
// return p.parking_code == code: Compares parking codes


// File Operations
void loadParks() {
    parks.clear();
    ifstream file("parks.csv");
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        Park p;
        string spaces;
        getline(ss, p.parking_code, ',');
        getline(ss, p.name, ',');
        getline(ss, spaces, ',');
        getline(ss, p.location);
        p.available_space = stoi(spaces);
        parks.push_back(p);
    }
}

void saveParks() {
    ofstream file("parks.csv");
    file << "Code,Name,AvailableSpaces,Location\n";
    for (const auto& p : parks)
        file << p.toCSV() << endl;
}

void loadGraph() {
    graph.clear();
    ifstream file("distances.csv");
    string line;
    getline(file, line); // skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string from, to, dist;
        getline(ss, from, ',');
        getline(ss, to, ',');
        getline(ss, dist);
        if (!from.empty() && !to.empty()) {
            graph[from].push_back({to, stoi(dist)});
        }
    }
}

void saveGraph() {
    ofstream file("distances.csv");
    file << "FromPark,ToPark,Distance\n";
    for (const auto& [from, distances] : graph) {
        for (const auto& dist : distances) {
            file << from << "," << dist.target << "," 
                 << dist.distance << "\n";
        }
    }
}

// CRUD Operations
void addPark() {
    Park p;
    cout << "Enter Parking Code: ";
    cin >> p.parking_code;
    if (parkExists(p.parking_code)) {
        cout << "Parking with this code already exists!\n";
        return;
    }
    
    cout << "Enter Park Name: ";
    cin.ignore();
    getline(cin, p.name);
    
    cout << "Enter Location: ";
    getline(cin, p.location);
    
    string spaces;
    cout << "Enter Available Spaces: ";
    getline(cin, spaces);
    if (!isNumber(spaces)) {
        cout << "Error: Available spaces must be a number.\n";
        return;
    }
    p.available_space = stoi(spaces);
    
    parks.push_back(p);
    saveParks();
    cout << "Parking added successfully.\n";
}

void addDistance() {
    string from, to;
    int distance;
    
    cout << "Enter source parking code: ";
    cin >> from;
    cout << "Enter destination parking code: ";
    cin >> to;
    
    if (!parkExists(from) || !parkExists(to)) {
        cout << "Error: One or both parking codes not found.\n";
        return;
    }
    
    cout << "Enter distance in meters: ";
    cin >> distance;
    
    // Add bidirectional connection
    graph[from].push_back({to, distance});
    graph[to].push_back({from, distance});
    
    saveGraph();
    cout << "Distance added successfully.\n";
}

void showParkingNetwork() {
    ofstream out("parking_network.csv");
    out << "Parking,Connected Parks,Details\n";
    
    cout << "\nParking Code | Connected Parks | Details\n";
    cout << "----------------------------------------\n";
    
    for (const auto& p : parks) {
        string connections;
        for (const auto& dist : graph[p.parking_code]) {
            connections += dist.target + "(" + 
                         to_string(dist.distance) + "m) ";
        }
        if (connections.empty()) connections = "None";
        
        string desc = p.description();
        cout << p.parking_code << " | " << connections << " | " 
             << desc << endl;
        out << p.parking_code << "," << connections << "," 
            << desc << "\n";
    }
    cout << "\nParking network saved to 'parking_network.csv'\n";
}

void removeEdge() {
    string from, to;
    cout << "Enter first parking code: ";
    cin >> from;
    cout << "Enter second parking code: ";
    cin >> to;
    
    if (!parkExists(from) || !parkExists(to)) {
        cout << "Error: One or both parking codes not found.\n";
        return;
    }

    // Remove edge in both directions (undirected graph)
    auto& fromDistances = graph[from];
    auto& toDistances = graph[to];
    
    // Remove 'to' from 'from's distances
    fromDistances.erase(
        remove_if(fromDistances.begin(), fromDistances.end(),
            [&](const Distance& d) { return d.target == to; }),
        fromDistances.end()
    );
    
    // Remove 'from' from 'to's distances
    toDistances.erase(
        remove_if(toDistances.begin(), toDistances.end(),
            [&](const Distance& d) { return d.target == from; }),
        toDistances.end()
    );
    
    saveGraph();
    cout << "Connection between " << from << " and " << to << " removed.\n";
}

void removePark() {
    string code;
    cout << "Enter parking code to remove: ";
    cin >> code;
    
    if (!parkExists(code)) {
        cout << "Error: Parking code not found.\n";
        return;
    }
    
    // Remove park from parks vector
    parks.erase(
        remove_if(parks.begin(), parks.end(),
            [&](const Park& p) { return p.parking_code == code; }),
        parks.end()
    );
    
    // Remove all edges connected to this park
    graph.erase(code);
    for (auto& [_, distances] : graph) {
        distances.erase(
            remove_if(distances.begin(), distances.end(),
                [&](const Distance& d) { return d.target == code; }),
            distances.end()
        );
    }
    
    saveParks();
    saveGraph();
    cout << "Parking " << code << " and all its connections removed.\n";
}

int main() {
    loadParks();
    loadGraph();
    
    int choice;
    do {
// In main(), update the menu:
cout << "\n--- Parking Network Management ---\n";
cout << "1. Add Parking\n";
cout << "2. Add Distance Between Parks\n";
cout << "3. Show Parking Network\n";
cout << "4. Remove Connection Between Parks\n";
cout << "5. Remove Parking\n";
cout << "0. Exit\n";

// Update switch statement:
switch (choice) {
    case 1: addPark(); break;
    case 2: addDistance(); break;
    case 3: showParkingNetwork(); break;
    case 4: removeEdge(); break;
    case 5: removePark(); break;
    case 0: cout << "Exiting...\n"; break;
    default: cout << "Invalid choice.\n";
}
    } while (choice != 0);
    
    return 0;
}