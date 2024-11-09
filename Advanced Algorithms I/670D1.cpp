// https://codeforces.com/contest/670/problem/D1
// https://codeforces.com/problemset/problem/670/D1

#include<bits/stdc++.h>
using namespace std;
long long n, k;
vector<long long> a, b;
bool canMake(long long m){
    long long tmp = k;
    for(int i = 0; i < n; i++){
        long long need = a[i]*m;
        if(need <= b[i])
            continue;
        tmp -= (need - b[i]);
        if(tmp < 0)
            return false;
    }
    return true;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> k;
    long long asum = 0;
    long long bsum = 0;
    for(int i = 0; i < n; i++){
        long long ai;
        cin >> ai;
        a.push_back(ai);
        asum += a[i];
    }
    for(int i = 0; i < n; i++){
        long long bi;
        cin >> bi;
        b.push_back(bi);
        bsum += b[i];
    }
    long long r = INT_MAX;
    long long l = 0;
    
    while(r > l){
        long long mid = ((l + r) / 2) + 1;
        if(canMake(mid))
            l = mid;
        else
            r = mid - 1;
    }
    cout << l << endl;
}