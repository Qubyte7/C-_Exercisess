#include<iostream>
using namespace std;

class Student{
    public:
        int student_id;
        string name;
        int age;
        string course;
        Student *next;
    Student(int student_id,string &name,int age,string &course):student_id(student_id),name(name),course(course){};
};





int main(){
    cout<<" ";

    return 0;
}