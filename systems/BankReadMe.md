1. ifstream (Input File Stream)

---

Used for reading FROM files
Can only read data
Example:
ifstream inFile("./files/database.csv"); // Opens file for reading
string line;
getline(inFile, line); 

2. ofstream (Output File Stream)

---

Used for writing TO files
Can only write data
Can create new files
Example:

ofstream outFile("./files/database.csv"); // Opens file for writing
outFile << "data,to,write" << endl;


3.ios::out is a file mode flag in C++ that:

Opens file for output operations (writing)
If file doesn't exist, creates it
If file exists, truncates it (erases all content)