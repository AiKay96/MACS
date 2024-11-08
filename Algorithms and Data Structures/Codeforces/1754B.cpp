// https://codeforces.com/contest/1754/problem/B
// https://codeforces.com/problemset/problem/1754/B

#include <bits/stdc++.h>
using namespace std;
int t, n;
string s;
int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        int mid = n/2 + 1;
        cout << mid << " ";
        for(int i = 1; i < mid; i++){
            cout << i << " ";
            if(i+mid <= n)
                cout << i + mid << " ";
        }
        cout << endl;
    }
}