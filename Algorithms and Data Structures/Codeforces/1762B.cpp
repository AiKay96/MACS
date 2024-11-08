// https://codeforces.com/contest/1762/problem/B
// https://codeforces.com/problemset/problem/1762/B

#include <bits/stdc++.h>
using namespace std;
int arr[100001], t, n, a;
set<long long> powOri;
int main(){
    std::ios::sync_with_stdio(false);
    int oru = 1;
    powOri.insert(oru);
    for(int i = 1; i < 31; i++){
        oru*=2;
        powOri.insert(oru);
    }
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> a;
            set<long long>::iterator ana = powOri.lower_bound(a);
            long long powOru = *ana;
            arr[i] = powOru - a;
        }
        cout << n << endl;
        for(int i = 0; i < n; i++){
            cout << i+1 << " " << arr[i] << endl;
        }
    }
}