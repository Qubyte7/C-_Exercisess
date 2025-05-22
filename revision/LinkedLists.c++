#include<iostream>
using namespace std;
// 1
class Student{
    public:
    string name;
    int age;
    string className;
    Student *next;
    Student(string studentName,int studentAge,string studentClassName):name(studentName),age(studentAge),className(studentClassName), next(NULL){};
};


void mapThroughTheList(Student *Head){
    while (Head != NULL)
    {
        cout<< Head->name <<" -> " ;
        Head  = Head->next;
    }

    cout<< "NULL" <<endl;
    
}

void reverseMap(Student *Head){
    Student *current = Head;
    Student *nextStudent = NULL;
    Student *prevStudent = NULL;
    while( current != NULL){
        //setting next Student
        nextStudent = current->next;
        //reversing the pointer of the current student to the previous Student
        current->next = prevStudent;
        // now we have to move pointer one position ahead
        prevStudent = current;
        current = nextStudent;
    }

        // Step 2: Print the reversed list starting from last node (prev)
    while (prevStudent!= NULL) {
        cout << prevStudent->name << " -> ";
        prevStudent = prevStudent->next;
    }
    cout << "NULL" << endl;


}

int main(){
    Student *student1 = new Student("innocent",18,"y3b");
    Student *student2 = new Student("burce",18,"y3c");
    Student *student3 = new Student("Hope",18,"Y3c");
    Student *student4 = new Student("dan",17,"y3a");
    Student * studen5 = new Student("Elisa",18,"y3d");

    student1->next = student2;
    student2->next  = student3;
    student3->next = student4;
    student4->next = studen5;

    mapThroughTheList(student1);
    reverseMap(student1);

    delete student1;
    delete student2;
    delete student3;
    delete student4;
    delete studen5;
    studen5 = nullptr;//prevent a dangling pointer
    student4 = nullptr;
    student3 = nullptr;
    student2 = nullptr;
    student1  = nullptr;

    

    return 0;

}