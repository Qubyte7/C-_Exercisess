#include<iostream>
#include<string>

using namespace std;

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

// The main function is the entry point of every C++ program.
// It can optionally take two arguments:
// argc: Argument count (integer) - The number of command-line arguments.
//       It will always be at least 1, as the program's name itself is the first argument.
// argv: Argument vector (array of character pointers) - An array of C-style strings,
//       where each string is one of the command-line arguments.
//       argv[0] is always the name of the program.
//       argv[1] is the first actual argument, argv[2] the second, and so on.

int main(int argc,char* argv[]){
    if(argc < 2){
        cout<<"Usage : "<<argv[0]<<"<command> [arguments...]"<<endl;
        cout<<"Commands:"<<endl;
        cout << "add <number1> <number2>  - Returns the sum of two numbers." << std::endl;
        return EXIT_SUCCESS; 
    }

    string command = argv[1];
    if(command == "add"){
        if(argc != 4){
            cout<<"number of arguments exceeded"<<endl;
            return EXIT_FAILURE;
        }
        int num1 = stringToInt(argv[2]);
        int num2 = stringToInt(argv[3]);
        int sum = num1 + num2 ;
        cout << "Oooh the sum is (0*-*o) ===:}> "<<sum<<endl;
    }else{
        // --- Handle unknown commands ---
        std::cerr << "Error: Unknown command '" << command << "'." << std::endl;
        std::cerr << "Type '" << argv[0] << "' for usage instructions." << std::endl;
        return EXIT_FAILURE; // Indicate an error
    }

return EXIT_SUCCESS;
}