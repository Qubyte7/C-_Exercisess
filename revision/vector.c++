#include<iostream>
#include<vector>

using namespace std;
int main(){
    vector<int> vector1= {1,2,3,4};
    int size = vector1.size();
    cout << "size "<<size<<endl;
    for(int i=0;i<=size;i++){
        cout<< vector1[i];
    }
    
    vector1.erase(vector1.begin() + 2, vector1.begin() + 3);
    return 0;
}