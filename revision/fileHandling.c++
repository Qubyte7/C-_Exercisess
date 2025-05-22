#include<iostream>
#include<fstream>
#include<string>

using namespace std;

void file(){
    ofstream outputFile("./files/test.txt");
    if (outputFile.is_open())
    {
        outputFile << " here this is the first line \n";
        outputFile <<" here is the 2nd line ";

        outputFile.close();
        cout<<" created and written to files ";
    }else{
        cout<< "failed to create a file ";
    }
    
};

void openAndDisplay(){
    ifstream inputFile("./files/test.txt");
    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            cout << line << endl;
        }
        inputFile.close();
        
    }else{
        cout<< " failed to read ! "<<endl;
    }
    
}

void writeToCSV(){
    ofstream csvFile("./files/data.csv");
    if (csvFile.is_open())
    {
                csvFile << "Name,Age,City\n";
        
        // Writing data rows
        csvFile << "John,25,New York\n";
        csvFile << "Alice,30,London\n";
        csvFile << "Bob,28,Paris\n";
        
        csvFile.close();
        cout << "Data successfully written to CSV file!" << endl;
    }else{
        cout << "failed to create CSV and write in csv !!!";
    }

    
}
/*
ifstream is an input file stream class used to read data from files.
ofstream is an output file stream class used to write data to files.

- ifstream objects are used for reading from files (input operations).
- ofstream objects are used for writing to files (output operations).
*/

int main(){
    cout<<"WELCOME TO FILE MANUPILATION :"<<endl<<"============================="<<endl;
    file();
    openAndDisplay();
    writeToCSV();
    return 0;
}