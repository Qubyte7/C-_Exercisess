#include<iostream>
#include<string>

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

int max(int arr[],int start,int end){
    if(start == end ){
        return arr[start];
    }

    int mid = (start+end)/2;
    int max1 = max(arr,start,mid);
    int max2 = max(arr,mid+1,end);

    return (max1 > max2)? max1 : max2 ;
};


bool isStringPalindrome(string text,int start_index,int last_index){
    if(start_index >= last_index){
        return true;
    }

    if(text[start_index] != text[last_index]){
        return false;
    }

    return isStringPalindrome(text,start_index +1,last_index - 1);
    
};


int main(){
    int arr[] = {1,2,3,4,5};
    int number = arr[4];
    int size = sizeof(arr)/sizeof(arr[0]);
    string name = "MenoneM";
    cout<<"sum of arr : "<< add(arr,size) << endl;
    cout<<"max number : "<< max(arr,0,size-1)<<endl;
    cout<<"Factorial of " <<number << " is " << factorial(number) << endl;
    cout<<"is " << name << " palindrome : "<< isStringPalindrome(name, 0, name.length() - 1);
    
    


    return 0;
}