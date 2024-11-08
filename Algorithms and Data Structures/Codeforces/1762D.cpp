// https://codeforces.com/contest/1762/problem/D
// https://codeforces.com/problemset/problem/1762/D

#include <bits/stdc++.h>
using namespace std;
int t, n, a;
int main(){
    std::ios::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        int x = 1;
        int y = 2;
        int g;
        cout << "? " << x << " " << y << endl;
        cin >> g;
        for(int i = 3; i <= n; i++){
            int g1, g2;
            cout << "? " << x << " " << i << endl;
            cin >> g1;
            cout << "? " << y << " " << i << endl;
            cin >> g2;
            if(g1 > g2 && g1 > g)
                y = i;
            else if(g2 > g)
                x = i;
            g = max(g, max(g1, g2));
        }
        cout << "! " << x << " " << y << endl;
        cin >> a;
        cout.flush();
    }
}