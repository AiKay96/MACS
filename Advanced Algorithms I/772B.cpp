// https://codeforces.com/contest/722/problem/B
// https://codeforces.com/problemset/problem/722/B

#include <bits/stdc++.h>
using namespace std;

double x[1001], y[1001];
 
int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    
    double ans = INT_MAX;
    x[n] = x[0];
    y[n] = y[0];
    x[n + 1] = x[1];
    y[n + 1] = y[1];
    
    for(int i = 0; i < n; i++){
        double p1 = y[i] - y[i + 2];
        double p2 = x[i + 2] - x[i];
        double p3 = x[i] * y[i + 2] - x[i + 2] * y[i];
        double sq = sqrt(p1 * p1 + p2 * p2);
        double dist = (p1 * x[i + 1] + p2 * y[i + 1] + p3) / sq;
        ans = min(ans, dist / 2.0);
    }
    
    cout << setprecision(10) << ans << endl;
}