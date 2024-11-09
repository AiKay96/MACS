// https://codeforces.com/contest/1810/problem/D
// https://codeforces.com/problemset/problem/1810/D

#include<bits/stdc++.h>
using namespace std;
#define int long long
main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        int n;
        cin >> n;
        int hmax = LLONG_MAX;
        int hmin = LLONG_MIN;
        for(int i = 0; i < n; i++){
            int type, a, b;
            cin >> type;
            if(type == 1){
                int d;
                cin >> a >> b >> d;
                int hminf = (a - b)*(d-1) + b + 1;
                if(d == 1)
                    hminf = 1;
                int hmaxf = (a - b)*(d-1) + a;
                if(hmaxf >= hmin)
                    hmax = min(hmax, hmaxf);
                else{
                    cout << 0 << " ";
                    continue;
                }
                if(hminf <= hmax)
                    hmin = max(hmin, hminf);
                else{
                    cout << 0 << " ";
                    continue;
                }
                //cout <<"h: " <<  hmin << " " << hmax << endl;
                cout << 1 << " ";
            }else{
                cin >> a >> b;
                if(hmin == LLONG_MIN){
                    cout << -1 << " ";
                    continue;
                }
                int tmp = hmin - a;
                int l = 1; int r = tmp / (a-b);
                if(r * (a-b) != tmp)
                    r++;
                r++;
                while(l < r){
                    int m = (l + r) / 2;
                    if((m-1)*(a-b) + a >= hmin)
                        r = m;
                    else
                        l = m + 1;
                }
                if(l*(a-b) + b + 1 <= hmax){
                    cout << -1 << " ";
                    //cout << "L = " << l << " ";
                }else
                    cout << l << " ";
            }
        }
        cout << endl;
    }
}