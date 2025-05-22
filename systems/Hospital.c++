#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;
struct Hospital {
    string id;
    string name;
    string location;
    int numberOfPatients;
    string toCSV() const {
        return id + "," + name + "," + location + "," + to_string(numberOfPatients);
    }
    string description() const {
        return "Name: " + name + ", Location: " + location + ", Patients: " + to_string(numberOfPatients);
    }
};
struct Link {
    string target;
    string description;
};
vector<Hospital> hospitals;
map<string, vector<Link>> graph;
// Utility
bool isNumber(const string& s) {
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}
bool hospitalExists(const string& id) {
    return any_of(hospitals.begin(), hospitals.end(), [&](const Hospital& h) {
        return h.id == id;
    });
}
// Load and Save
void loadHospitals() {
    hospitals.clear();
    ifstream file("hospitals.csv");
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        Hospital h;
        string patients;
        getline(ss, h.id, ',');
        getline(ss, h.name, ',');
        getline(ss, h.location, ',');
        getline(ss, patients);
        h.numberOfPatients = stoi(patients);
        hospitals.push_back(h);
    }
}
void saveHospitals() {
    ofstream file("hospitals.csv");
    file << "ID,Name,Location,Patients\n";
    for (const auto& h : hospitals)
        file << h.toCSV() << endl;
}
void loadGraph() {
    graph.clear();
    ifstream file("graph.csv");
    string line;
    getline(file, line); // skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string from, to, desc;
        getline(ss, from, ',');
        getline(ss, to, ',');
        getline(ss, desc);
        if (!from.empty() && !to.empty()) {
            graph[from].push_back({to, desc});
        }
    }
}
void saveGraph() {
    ofstream file("graph.csv");
    file << "From,To,Description\n";
    for (const auto& [from, links] : graph) {
        for (const auto& link : links) {
            file << from << "," << link.target << "," << link.description << "\n";
        }
    }
}
// CRUD Functions
void addHospital() {
    Hospital h;
    cout << "Enter Hospital ID: ";
    cin >> h.id;
    if (hospitalExists(h.id)) {
        cout << "Hospital with this ID already exists!\n";
        return;
    }
    cout << "Enter Hospital Name: ";
    cin.ignore();
    getline(cin, h.name);
    cout << "Enter Location: ";
    getline(cin, h.location);
    string num;
    cout << "Enter Number of Patients: ";
    getline(cin, num);
    if (!isNumber(num)) {
        cout << "Error: Number of patients must be a number.\n";
        return;
    }
    h.numberOfPatients = stoi(num);
    hospitals.push_back(h);
    saveHospitals();
    cout << "Hospital added.\n";
}
void deleteHospital() {
    string id;
    cout << "Enter ID of hospital to delete: ";
    cin >> id;
    if (!hospitalExists(id)) {
        cout << "Hospital not found.\n";
        return;
    }
    hospitals.erase(remove_if(hospitals.begin(), hospitals.end(),
                              [&](Hospital h) { return h.id == id; }), hospitals.end());
    graph.erase(id);
    for (auto& [_, neighbors] : graph) {
        neighbors.erase(remove_if(neighbors.begin(), neighbors.end(),
                                  [&](Link l) { return l.target == id; }), neighbors.end());
    }
    saveHospitals();
    saveGraph();
    cout << "Hospital deleted.\n";
}
void updateHospital() {
    string id;
    cout << "Enter ID of hospital to update: ";
    cin >> id;
    for (auto& h : hospitals) {
        if (h.id == id) {
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, h.name);
            cout << "Enter new location: ";
            getline(cin, h.location);
            string num;
            cout << "Enter new number of patients: ";
            getline(cin, num);
            if (!isNumber(num)) {
                cout << "Error: Patients must be a number.\n";
                return;
            }
            h.numberOfPatients = stoi(num);
            saveHospitals();
            cout << "Hospital updated.\n";
            return;
        }
    }
    cout << "Hospital not found.\n";
}
void addConnection() {
    string from, to, desc;
    cout << "Enter source hospital ID: ";
    cin >> from;
    cout << "Enter destination hospital ID: ";
    cin >> to;
    if (!hospitalExists(from) || !hospitalExists(to)) {
        cout << "Error: One or both hospital IDs not found.\n";
        return;
    }
    for (const auto& l : graph[from])
        if (l.target == to) {
            cout << "Connection already exists.\n";
            return;
        }
    cout << "Enter description of the link (e.g., 'Ambulance route'): ";
    cin.ignore();
    getline(cin, desc);
    graph[from].push_back({to, desc});
    graph[to].push_back({from, desc}); // bidirectional
    saveGraph();
    cout << "Connection added.\n";
}
void showTable() {
    ofstream out("relationship_table.csv");
    out << "Hospital Center,Connected Hospitals,Description\n";
    cout << "\nHospital Center | Connected Hospitals       | Description\n";
    cout << "-------------------------------------------------------------\n";
    for (const auto& h : hospitals) {
        string links;
        for (const auto& link : graph[h.id]) {
            links += link.target + "(" + link.description + ") ";
        }
        if (links.empty()) links = "None";
        string desc = h.description();
        cout << h.id << "              | " << links << "| " << desc << endl;
        out << h.id << "," << links << "," << desc << "\n";
    }
    cout << "\nRelationship table saved to 'relationship_table.csv'.\n";
}
// Menu
int main() {
    loadHospitals();
    loadGraph();
    int choice;
    do {
        cout << "\n--- Hospital Network Management ---\n";
        cout << "1. Add Hospital\n";
        cout << "2. Delete Hospital\n";
        cout << "3. Update Hospital\n";
        cout << "4. Add Connection\n";
        cout << "5. Show Relationship Table\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addHospital(); break;
            case 2: deleteHospital(); break;
            case 3: updateHospital(); break;
            case 4: addConnection(); break;
            case 5: showTable(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}