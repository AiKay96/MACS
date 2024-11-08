// https://codeforces.com/contest/1772/problem/D
// https://codeforces.com/problemset/problem/1772/D

#include <bits/stdc++.h>
using namespace std;
int t, n, m, k, a, b, c, d;
string s;
long long sashualo(long long x, long long y){
    long long p = x + y;
    if(p%2 == 1)
        p++;
    return p/2;
}
int main(){
    std::ios::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        long long arr[n];
        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }
        long long dpmax[n], dpmin[n];
        if(arr[0] == arr[1]){
                dpmin[0] = 0;
                dpmax[0] = INT_MAX;
        }else if(arr[0] < arr[1]){
            dpmin[0] = 0;
            dpmax[0] = (arr[0] + arr[1]) / 2;
        }else{
            dpmax[0] = INT_MAX;
            dpmin[0] = sashualo(arr[0], arr[1]);
        }
        bool cant = false;
        for(int i = 1; i < n-1; i++){
            if(arr[i] == arr[i+1]){
                dpmax[i] = dpmax[i-1];
                dpmin[i] = dpmin[i-1];
            }else if(arr[i] < arr[i+1]){
                if(abs(arr[i+1] - dpmin[i-1]) < abs(arr[i] - dpmin[i-1])){
                    cant = true;
                    break;
                }else{
                    dpmin[i] = dpmin[i-1];
                    dpmax[i] = min((arr[i] + arr[i+1]) / 2, dpmax[i-1]);
                }
            }else{
                if(abs(arr[i+1] - dpmax[i-1]) < abs(arr[i] - dpmax[i-1])){
                    cant = true;
                    break;
                }else{
                    dpmin[i] = max(sashualo(arr[i], arr[i+1]), dpmin[i-1]);
                    dpmax[i] = dpmax[i-1];
                }
            }
        }
        
        if(cant){
            cout << -1 << endl;
        }else{
            cout << dpmin[n-2] << endl;
        }
    }
}