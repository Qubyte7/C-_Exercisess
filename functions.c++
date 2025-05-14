#include<iostream>
using namespace std;

// recursion

int add(int arr[],int size){
    if (size == 0 ) return 0;
    return arr[size-1] + add(arr,size-1);
};

int factorial(int n){
    if (n == 1)
    {
     return 1;
    }
    return n*factorial(n-1);
}


int main(){
    int arr[] = {1,2,3,4,5};
    int number = arr[4];
    int size = sizeof(arr)/sizeof(arr[0]);
    cout<<"sum of arr : "<< add(arr,size) << endl;
    cout<<" factorial of " <<
    


    return 0;
}