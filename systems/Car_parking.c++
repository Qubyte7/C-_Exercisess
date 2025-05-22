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

int main() {
    loadParks();
    loadGraph();
    
    int choice;
    do {
        cout << "\n--- Parking Network Management ---\n";
        cout << "1. Add Parking\n";
        cout << "2. Add Distance Between Parks\n";
        cout << "3. Show Parking Network\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: addPark(); break;
            case 2: addDistance(); break;
            case 3: showParkingNetwork(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    
    return 0;
}