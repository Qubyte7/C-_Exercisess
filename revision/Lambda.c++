#include<iostream>

using namespace std;

// [&]: capture all external variables by reference.
// [=]: capture all external variables by value.
// [a, &b]: capture 'a' by value and 'b' by reference.


int main(int argc,char*argv[]){
    
    auto res = [](int x){
        return x*2;
    };

    cout<<res(5);
    return 0;
}