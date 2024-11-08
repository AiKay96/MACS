// https://codeforces.com/contest/1766/problem/A
// https://codeforces.com/problemset/problem/1766/A

#include <bits/stdc++.h>
using namespace std;

int calculate(int n){
    if(n < 10){
        return n;
    }else{
        return 9 + calculate(n/10);
    }
}
int main(){
    int t, n;
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        cout << calculate(n) << endl;
    }
}