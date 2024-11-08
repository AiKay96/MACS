// https://codeforces.com/contest/1788/problem/C
// https://codeforces.com/problemset/problem/1788/C

#include <bits/stdc++.h>
using namespace std;
long long n, m, a, b;
int main(){
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        if(n % 2 == 0){
            cout << "No" << endl;
        }else{
            cout << "Yes" << endl;
            cout << 1 << " " << 2*n << endl;
            long long sum = 1 + 2*n;
            long long start = 1;
            for(int i = 0; i < n/2; i++){
                sum--;
                start++;
                cout << start << " " << sum - start << endl;
            }
            sum = 1 + 2*n + n/2 + 1;
            for(int i = 0; i < n/2; i++){
                sum--;
                start++;
                cout << start << " " << sum - start << endl;
            }
        }
    }
}