// https://codeforces.com/contest/466/problem/C
// https://codeforces.com/problemset/problem/466/C

#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    long long arr[n];
    long long a;
    cin >> a;
    arr[0] = a;
    for(int i = 1; i < n; i++){
        cin >> a;
        arr[i] = arr[i-1] + a;
    }
    if(arr[n-1]%3 != 0){
        cout << 0 << endl;
        return 0;
    }
    long long part1 = arr[n-1]/3;
    long long part2 = part1*2;
    long long numP1 = 0;
    long long ans = 0;
    for(int i = 0; i < n-1; i++){
        if(arr[i] == part2)
            ans+=numP1;
        if(arr[i] == part1)
            numP1++;
    }
    cout << ans << endl;
}