// https://codeforces.com/contest/530/problem/C
// https://codeforces.com/problemset/problem/530/C

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int a, b, c;
    cin >> a >> b >> c;
    int x = 0;
    int y = 0;
    int gcdu = __gcd(a,b);
    if(a + b > c || c % gcdu != 0){
        cout << 0 << endl;
        return 0;
    }
    a /= gcdu;
    b /= gcdu;
    c /= gcdu;
    while(true){
        x++;
        if((c - a*x) % b == 0){
            y = (c - a*x)/b;
            break;
        }
    }
    vector<pair<int, int> > ans;
    while(y > 0){
        ans.push_back({x, y});
        x+=b;
        y-=a;
    }
    cout << ans.size() << endl;
    for(int i = 0; i < ans.size(); i++)
        cout << ans[i].first << " " << ans[i].second << endl;
}