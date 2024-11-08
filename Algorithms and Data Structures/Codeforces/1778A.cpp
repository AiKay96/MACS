// https://codeforces.com/contest/1778/problem/A
// https://codeforces.com/problemset/problem/1778/A

#include <bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        int n;
        cin >> n;
        int k, a, b;
        int arr[n];
        int sum = 0;
        for(int i = 0; i < n; i++){
            cin >> arr[i];
            sum += arr[i];
        }
        int jam[n];
        for(int i = 1; i < n; i++)
            jam[i] = arr[i] + arr[i-1];
        jam[0] = INT_MAX;
        sort(jam, jam + n);
        if(jam[0] == -2){
            cout << sum + 4 << endl;
        }else if(jam[0] == 0){
            cout << sum << endl;
        }else{
            cout << sum - 4 << endl;
        }
    }
}