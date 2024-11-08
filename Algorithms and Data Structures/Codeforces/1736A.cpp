// https://codeforces.com/contest/1736/problem/A
// https://codeforces.com/problemset/problem/1736/A

#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        int n;
        cin >> n;
        int a[n], b[n], sum[n];
        for(int i = 0; i < n; i++)
            cin >> a[i];
        for(int i = 0; i < n; i++){
            cin >> b[i];
            sum[i] = b[i] - a[i];
        }
        int minus = 0;
        int plus = 0;
        for(int i = 0; i < n; i++){
            if(sum[i] < 0)
                minus++;
            if(sum[i] > 0)
                plus++;
            if(i > 0)
                sum[i] += sum[i-1];
        }
        sum[n-1] = abs(sum[n-1]);
        if(minus > 0 && plus > 0)
            sum[n-1]++;
        cout << sum[n-1] << endl;
    }
}