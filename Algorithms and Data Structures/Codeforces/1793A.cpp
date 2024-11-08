// https://codeforces.com/contest/1793/problem/A
// https://codeforces.com/problemset/problem/1793/A

#include <bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        long long a, b;
        cin >> a >> b;
        long long n, m;
        cin >> n >> m;
        long long price = 0;
        long long num = 0;
        if(a * m < b * (m + 1)){
            price += a*m*(n / (m+1));
            num += n/(m+1) * (m+1);
        }else{
            price += b*n;
            cout << price << endl;
            continue;
        }
        long long left = n - num;
        price += min(left * min(a, b), m*a);
        cout << price << endl;
    }
}