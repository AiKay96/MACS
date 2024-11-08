// https://codeforces.com/contest/1734/problem/B
// https://codeforces.com/problemset/problem/1734/B

#include <bits/stdc++.h>
using namespace std;
int arr[501][501];
int main(){
    int t;
    cin >> t;
    arr[0][0] = 1;
    for(int i = 1; i < 500; i++){
        arr[i][0] = 1;
        arr[i][i] = 1;
    }
    for(int r = 0; r < t; r++){
        int n;
        cin >> n;
        for(int i = 0; i < n; i++){
            for(int j = 0; j <= i; j++)
                cout << arr[i][j] << " ";
            cout << endl;
        }
    }
}