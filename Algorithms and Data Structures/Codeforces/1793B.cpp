// https://codeforces.com/contest/1793/problem/B
// https://codeforces.com/problemset/problem/1793/B

#include <bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        int a, b;
        cin >> a >> b;
        cout << (a - b)*2 << endl;
        for(int i = a; i >= b; i--)
            cout << i << " ";
        for(int i = b + 1; i < a; i++)
            cout << i << " ";
        cout << endl;
    }
}