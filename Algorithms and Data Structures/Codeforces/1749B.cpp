// https://codeforces.com/contest/1749/problem/B
// https://codeforces.com/problemset/problem/1749/B

#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        int n;
        cin >> n;
        long long a[n], b[n];
        long long sum = 0;
        for(int i = 0; i <n ; i++){
            cin >> a[i];
            sum += a[i];
        }
        long long maxN = 0;
        for(int i = 0; i <n ; i++){
            cin >> b[i];
            sum += b[i];
            maxN = max(maxN, b[i]);
        }
        cout << sum - maxN << endl;
    }
}