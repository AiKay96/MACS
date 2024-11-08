// https://codeforces.com/gym/102911/problem/D
// https://codeforces.com/problemset/gymProblem/102911/D

#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    if(n%4 == 0)
        cout << "0" << endl;
    if(n%4 == 1){
        cout << "1" << endl;
        cout << "A";
        n--;
    }
    if(n%4 == 2){
        cout << "1" << endl;
        cout << "AB";
        n-=2;
    }
    if(n%4 == 3){
        cout << "0" << endl;
        cout << "AAB";
        n-=3;
    }
    for(int i = 0; i < n; i+=4){
        cout << "ABBA";
    }
    cout << endl;
}