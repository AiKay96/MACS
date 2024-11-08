// https://codeforces.com/contest/1772/problem/B
// https://codeforces.com/problemset/problem/1772/B

#include <bits/stdc++.h>
using namespace std;
int t, n, m, k, a, b, c, d;
string s;
int main(){
    std::ios::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> a >> b >> c >> d;
        int mini = min(min(a,b), min(c,d));
        int maxi = max(max(a,b), max(c,d));
        if(a == mini){
            if(d == maxi)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }else if(b == mini){
            if(c == maxi)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
            
        }else if(c == mini){
            if(b == maxi)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
            
        }else{
            if(a == maxi)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }
}