#include<iostream>
#include<string>
#include<sstream>

using namespace std;


struct ItemStructure
{
    int item_id;
    string item_name;
    int item_quantity;
    string item_registration_date;
    ItemStructure *next;
};

class Item{
    public:
    ItemStructure *item;
    Item():item(nullptr){};

    void displayAllitems(bool sorted = true){
        if (sorted) {
            sortByItemId();  // Sort before displaying
        }
        ItemStructure *temp = item;
        while (temp != NULL)
        {
            cout<<"Item ID :"<<temp->item_id<<"     Item Name :"<<temp->item_name
            <<"     Quantity :"<<temp->item_quantity<<"   reg Date :"<<temp->item_registration_date<<endl;
         temp = temp->next;   
        }
    }

    void addNewItemAtLast(int id,string& name,int quantity,string& reg_date){
            ItemStructure *newItem = new ItemStructure;
            newItem->item_id = id;
            newItem->item_name = name;
            newItem->item_quantity = quantity;
            newItem->item_registration_date = reg_date;
            newItem->next = nullptr;

            if(item == nullptr){
                item = newItem;
                item->next = nullptr;
                return;
            }
            ItemStructure *temp = item;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newItem;
            newItem->next = nullptr;
        }

    void sortByItemId(){
        if(item == nullptr || item->next == nullptr){
            return;
        }

        bool swapped;
        ItemStructure *ptr1;
        ItemStructure *lptr = nullptr;

        do{
            swapped = false;
            ptr1 = item;
            while(ptr1->next != lptr){
                if(ptr1->item_id > ptr1->next->item_id){
                    swap(ptr1->item_id, ptr1->next->item_id);
                    swap(ptr1->item_name, ptr1->next->item_name);
                    swap(ptr1->item_quantity, ptr1->next->item_quantity);
                    swap(ptr1->item_registration_date, ptr1->next->item_registration_date);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        }while (swapped);
        
    }

        ~Item() {
        ItemStructure* current = item;
        while (current != nullptr) {
            ItemStructure* next = current->next;
            delete current;
            current = next;
        }
    }

// Automatically called when an Item object goes out of scope
// Traverses through all nodes in the linked list
// Properly deallocates each node's memory
// Prevents memory leaks

};

int stringToInt(const string& str){
    try{
        return stoi(str);
    }catch(const invalid_argument& e){
        cerr<<"Eroor :Invalid number format for"<<str <<endl ;
        exit(EXIT_FAILURE);
    }catch (const std::out_of_range& e) {
        // Catch out of range exception (e.g., if the number is too large for an int)
        std::cerr << "Error: Number '" << str << "' is out of integer range." << std::endl;
        exit(EXIT_FAILURE); // Exit the program with an error code
    }
}


int main(int argc, char* argv[]) {
    cout << "Hello THERE !" << endl;
    cout << "Type 'help' for available commands or 'exit' to quit" << endl;

    Item inventory;
    string command;

    while (true) {
        cout << "\nEnter command: ";
        getline(cin, command);

        if (command == "exit") {
            cout << "Thank you for using our system!" << endl;
            break;
        }
        else if (command == "help") {
            cout << "---------------------------------------" << endl
                 << "*        Commands syntaxes           *" << endl
                 << "----------------------------------------" << endl;
            cout << "itemadd <item_id> <item_name> <quantity> <Registration_date>" << endl;
            cout << "itemslist" << endl;
            cout << "exit" << endl;
        }
        else if (command.substr(0, 7) == "itemadd") {
            // Parse the command string for arguments
            stringstream ss(command);
            string cmd, id_str, name, quantity_str, date;
            ss >> cmd >> id_str >> name >> quantity_str >> date;

            if (cmd.empty() || id_str.empty() || name.empty() || quantity_str.empty() || date.empty()) {
                cout << "Invalid arguments!" << endl;
                cout << "Correct syntax: itemadd <item_id> <item_name> <quantity> <Registration_date>" << endl;
                continue;
            }

            try {
                int item_id = stringToInt(id_str);
                int quantity = stringToInt(quantity_str);
                inventory.addNewItemAtLast(item_id, name, quantity, date);
                cout << "New Item added successfully!" << endl;
            }
            catch (...) {
                cout << "Invalid number format!" << endl;
            }
        }
        else if (command == "itemslist") {
            inventory.displayAllitems();
        }
        else {
            cout << "Unknown command. Type 'help' for available commands." << endl;
        }
    }
}





