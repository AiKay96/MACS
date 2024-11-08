// https://codeforces.com/contest/1737/problem/C
// https://codeforces.com/problemset/problem/1737/C

#include <bits/stdc++.h>
using namespace std;
int t, d, x1, y1, x2, y2, x3, y3, x0, y0;
int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> d;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        cin >> x0 >> y0;
        int wx, wy;
        if((x1 == x2 && y1 == y3) || (x1 == x3 && y1 == y2)){
            wx = x1;
            wy = y1;
        }
        if((x2 == x3 && y2 == y1) || (x2 == x1 && y2 == y3)){
            wx = x2;
            wy = y2;
        }
        if((x3 == x2 && y3 == y1) || (x3 == x1 && y3 == y2)){
            wx = x3;
            wy = y3;
        }
        if(wx == 1 && wy == 1){
            if(x0 == 1 || y0 == 1)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
            continue;
        }
        if(wx == 1 && wy == d){
            if(x0 == 1 || y0 == d)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
            continue;
        }
        if(wx == d && wy == 1){
            if(x0 == d || y0 == 1)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
            continue;
        }
        if(wx == d && wy == d){
            if(x0 == d || y0 == d)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
            continue;
        }
        wx%=2;
        wy%=2;
        x0%=2;
        y0%=2;
        if(wx == x0 || wy == y0)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}