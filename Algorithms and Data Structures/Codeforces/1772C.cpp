// https://codeforces.com/contest/1772/problem/C
// https://codeforces.com/problemset/problem/1772/C

#include <bits/stdc++.h>
using namespace std;
int t, n, m, k, a, b, c, d;
string s;
int main(){
    std::ios::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> k >> n;
        int start = n - k + 1;
        int arr[k];
        arr[0] = start;
        for(int i = 1; i < k; i++){
            arr[i] = arr[i-1] + 1;
        }
        for(int i = 1; i < 10; i++){
            if(arr[0] - i > 0){
                for(int j = 0; j < i; j++){
                    arr[j] -= i;
                }
            }else{
                break;
            }
        }
        for(int i = 0; i < k; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}