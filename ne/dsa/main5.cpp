#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip> // For output formatting
#include <algorithm> // For max
#include<limits>

using namespace std;

// --- Data Structures ---
struct City {
    int id;
    string name;
};
vector<City> cities;
vector<vector<int>> road_matrix;
vector<vector<double>> budget_matrix;
const string CITIES_FILE = "cities.txt";
const string ROADS_FILE = "roads.txt";
int max_city_id = 0; // Tracks the highest city ID in use

// --- Helper Functions ---
// Resizes matrices to fit up to max_city_id (0 to max_city_id-1 indices)
void resize_matrices_if_needed() {
    if (max_city_id == 0) { // No cities, clear matrices
        road_matrix.clear();
        budget_matrix.clear();
        return;
    }
    // Only resize if current matrix size is smaller than max_city_id
    if (static_cast<int>(road_matrix.size()) < max_city_id) {
        // Preserve existing data
        vector<vector<int>> temp_r = road_matrix;
        vector<vector<double>> temp_b = budget_matrix;

        road_matrix.assign(max_city_id, vector<int>(max_city_id, 0));
        budget_matrix.assign(max_city_id, vector<double>(max_city_id, 0.0));

        for(size_t r=0; r < temp_r.size() && r < (size_t)max_city_id; ++r) {
            for(size_t c=0; c < temp_r[r].size() && c < (size_t)max_city_id; ++c) {
                if (r < road_matrix.size() && c < road_matrix[r].size()) road_matrix[r][c] = temp_r[r][c];
                if (r < budget_matrix.size() && c < budget_matrix[r].size()) budget_matrix[r][c] = temp_b[r][c];
            }
        }
    }
}

int get_city_id_by_name(const string& name) {
    for (const auto& city : cities) {
        if (city.name == name) return city.id;
    }
    return 0; // Not found
}

string get_city_name_by_id(int id) {
    for (const auto& city : cities) {
        if (city.id == id) return city.name;
    }
    return ""; // Not found
}

void load_data() {
    cities.clear();
    max_city_id = 0;
    ifstream c_file(CITIES_FILE);
    string line;
    while (getline(c_file, line)) {
        stringstream ss(line);
        string id_str, name_part;
        if (getline(ss, id_str, ':') && getline(ss, name_part)) {
            size_t first_char = name_part.find_first_not_of(" \t");
            if (first_char != string::npos) name_part = name_part.substr(first_char); else name_part = "";
            try {
                int id = stoi(id_str);
                cities.push_back({id, name_part});
                if (id > max_city_id) max_city_id = id;
            } catch (const exception&) { /* ignore malformed line */ }
        }
    }
    c_file.close();
    resize_matrices_if_needed(); // Resize based on loaded cities

    if (max_city_id == 0) return; // No cities, so no roads/budgets to link

    ifstream r_file(ROADS_FILE);
    while (getline(r_file, line)) {
        stringstream ss(line);
        string road_part, budget_str;
        size_t last_space = line.find_last_of(" \t");
        if (last_space == string::npos) continue;
        road_part = line.substr(0, last_space);
        budget_str = line.substr(last_space + 1);
        
        size_t dash = road_part.find('-');
        if (dash == string::npos || dash == 0 || dash == road_part.length() -1) continue;
        string c1_name = road_part.substr(0, dash);
        string c2_name = road_part.substr(dash + 1);
        int id1 = get_city_id_by_name(c1_name);
        int id2 = get_city_id_by_name(c2_name);
        // Ensure IDs are valid and within matrix bounds (1-based ID to 0-based index)
        if (id1 > 0 && id2 > 0 && (id1-1) < max_city_id && (id2-1) < max_city_id) {
            try {
                double budget = stod(budget_str);
                road_matrix[id1-1][id2-1] = 1; road_matrix[id2-1][id1-1] = 1;
                budget_matrix[id1-1][id2-1] = budget; budget_matrix[id2-1][id1-1] = budget;
            } catch (const exception&) { /* ignore malformed budget */ }
        }
    }
    r_file.close();
}

void save_cities() {
    ofstream file(CITIES_FILE);
    if (!file.is_open()) { cerr << "Error saving cities!\n"; return; }
    // Sort by ID for consistent file output (optional but good)
    sort(cities.begin(), cities.end(), [](const City& a, const City& b){ return a.id < b.id; });
    for (const auto& city : cities) {
        file << city.id << ": " << city.name << endl;
    }
    file.close();
}

// --- Menu Functions ---
void add_new_cities() {
    int num_to_add;
    cout << "Enter the number of cities to add: ";
    cin >> num_to_add; cin.ignore(); // Consume newline
    if (num_to_add <= 0) { cout << "Invalid number.\n"; return; }

    int next_id_to_assign = max_city_id + 1; // Start assigning IDs from here
    for (int i = 0; i < num_to_add; ++i) {
        string name;
        cout << "Enter name for city " << next_id_to_assign << ": ";
        getline(cin, name);
        if (name.empty()) { cout << "Name cannot be empty. Skipping.\n"; continue;}
        cities.push_back({next_id_to_assign, name});
        if (next_id_to_assign > max_city_id) max_city_id = next_id_to_assign;
        next_id_to_assign++;
    }
    save_cities();
    resize_matrices_if_needed(); // Resize if new cities increased max_city_id
    cout << "Cities added.\n";
}

void add_road_between_cities() {
    string n1, n2;
    cout << "Enter name of first city: "; getline(cin, n1);
    cout << "Enter name of second city: "; getline(cin, n2);
    int id1 = get_city_id_by_name(n1);
    int id2 = get_city_id_by_name(n2);
    if (id1 == 0 || id2 == 0) { cout << "One or both cities not registered.\n"; return; }
    if (id1 == id2) { cout << "Cannot add road to itself.\n"; return; }
    if ((id1-1) >= max_city_id || (id2-1) >= max_city_id || road_matrix.empty()) {
        cout << "City ID out of bounds for matrix or matrix not initialized. (Max ID: " << max_city_id <<")\n"; return;
    }
    road_matrix[id1-1][id2-1] = 1; road_matrix[id2-1][id1-1] = 1;
    cout << "Road added successfully.\n";
}

void add_budget_for_road() {
    string n1, n2; double budget;
    cout << "Enter name of first city: "; getline(cin, n1);
    cout << "Enter name of second city: "; getline(cin, n2);
    int id1 = get_city_id_by_name(n1);
    int id2 = get_city_id_by_name(n2);

    if (id1 == 0 || id2 == 0) { cout << "One or both cities not registered.\n"; return; }
    if ((id1-1) >= max_city_id || (id2-1) >= max_city_id || road_matrix.empty() || road_matrix[id1-1][id2-1] == 0) {
        cout << "No road between specified cities to add budget.\n"; return;
    }
    cout << "Enter budget for the road: "; cin >> budget; cin.ignore();
    if (budget < 0) { cout << "Budget cannot be negative.\n"; return; }

    budget_matrix[id1-1][id2-1] = budget; budget_matrix[id2-1][id1-1] = budget;
    
    ofstream r_file(ROADS_FILE, ios::app); // Append mode
    if (!r_file.is_open()) { cerr << "Error opening roads file for append!\n"; return; }
    r_file << n1 << "-" << n2 << " " << fixed << setprecision(1) << budget << endl;
    r_file.close();
    cout << "Budget added for the road between " << n1 << " and " << n2 << ".\n";
}

void edit_city() {
    int id_to_edit; string new_name;
    cout << "Enter index (ID) of city to edit: "; cin >> id_to_edit; cin.ignore();
    bool found = false;
    for (auto& city : cities) { // Use reference to modify directly
        if (city.id == id_to_edit) {
            cout << "Current name: " << city.name << ". Enter new name: ";
            getline(cin, new_name);
            if (new_name.empty()) {cout << "Name cannot be empty.\n"; return;}
            city.name = new_name;
            found = true; break;
        }
    }
    if (found) { 
        save_cities(); 
        cout << "City updated in cities.txt. Note: roads.txt not updated with new name.\n";
    } else { cout << "City not found.\n"; }
}

void search_city_by_index() {
    int id_to_search; 
    cout << "Enter index (ID) of city: "; cin >> id_to_search; cin.ignore();
    string name = get_city_name_by_id(id_to_search);
    if (!name.empty()) cout << "City " << id_to_search << ": " << name << endl;
    else cout << "City not registered.\n";
}

void display_cities() {
    cout << "\n--- List of Cities ---\n";
    if (cities.empty()) {cout << "No cities registered.\n"; return;}
    // Sort by ID for consistent display (optional but good)
    vector<City> sorted_cities = cities;
    sort(sorted_cities.begin(), sorted_cities.end(), [](const City& a, const City& b){ return a.id < b.id; });
    for (const auto& city : sorted_cities) cout << city.id << ": " << city.name << endl;
}

void display_matrix_output(const string& title, bool is_budget_matrix) {
    cout << "\n" << title << " Adjacency Matrix\n"; // Prompt used "adjaceny"
    if (max_city_id == 0 || (is_budget_matrix ? budget_matrix.empty() : road_matrix.empty()) ) {
         cout << "(No data or cities to display matrix for)\n"; return;
    }
    // Determine actual display size based on matrix content, up to max_city_id
    int display_dim = max_city_id;

    for (int i = 0; i < display_dim; ++i) {
        for (int j = 0; j < display_dim; ++j) {
            if (is_budget_matrix) {
                 // Ensure i and j are within bounds of budget_matrix
                if (i < static_cast<int>(budget_matrix.size()) && j < static_cast<int>(budget_matrix[i].size())) {
                    cout << fixed << setprecision(1) << budget_matrix[i][j] << "\t";
                } else {
                    cout << fixed << setprecision(1) << 0.0; // Default if out of bounds
                }
            } else {
                // Ensure i and j are within bounds of road_matrix
                if (i < static_cast<int>(road_matrix.size()) && j < static_cast<int>(road_matrix[i].size())) {
                    cout << road_matrix[i][j] <<"\t";
                } else {
                    cout << "0"; // Default if out of bounds
                }
            }
            if (is_budget_matrix && j < display_dim - 1) cout << " "; // Space for budget matrix as per example
        }
        cout << endl;
    }
}

// --- Main ---
int main() {
    load_data(); // Load all data at the start
    int choice;
    do {
        cout << "\nRoad Budget Management System\n"
                  << "1. Add New City(ies)\n"
                  << "2. Add Roads between Cities\n"
                  << "3. Add Budget for Roads\n"
                  << "4. Edit City\n"
                  << "5. Search for a City using its Index\n"
                  << "6. Display Cities\n"
                  << "7. Display Roads (Adjacency Matrix)\n"
                  << "8. Display Recorded Data on Console\n"
                  << "9. Exit\n"
                  << "Enter your choice: ";
        if (!(cin >> choice)) { // Basic input validation
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Consume newline

        switch (choice) {
            case 1: add_new_cities(); break;
            case 2: add_road_between_cities(); break;
            case 3: add_budget_for_road(); break;
            case 4: edit_city(); break;
            case 5: search_city_by_index(); break;
            case 6: display_cities(); break;
            case 7: display_matrix_output("Roads", false); break;
            case 8: display_matrix_output("Roads", false); display_matrix_output("Budgets", true); break;
            case 9: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);
    return 0;
}