// https://codeforces.com/contest/1010/problem/A
// https://codeforces.com/problemset/problem/1010/A

#include<bits/stdc++.h>
using namespace std;

int main(){
  	ios_base::sync_with_stdio(false);
    int n;
    double m;
    cin >> n >> m;
    double a[n], b[n];
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i < n; i++)
        cin >> b[i];
    double s = m;
    if(b[0] <= 1){
        cout << -1 << endl;
        return 0;
    }
    double t = s / (b[0] - 1);
    s+=t;
    for(int i = n - 1; i > 0; i--){
        t = s / (a[i] - 1);
        if(a[i] <= 1){
            cout << -1 << endl;
            return 0;
        }
        s += t;
        t = s / (b[i] - 1);
        if(b[i] <= 1){
            cout << -1 << endl;
            return 0;
        }
        s += t;
    }
    if(a[0] <= 1){
        cout << -1 << endl;
        return 0;
    }
    t = s / (a[0] - 1);
    s += t;
    s -= m;
    cout << setprecision(15) << s << endl;
}