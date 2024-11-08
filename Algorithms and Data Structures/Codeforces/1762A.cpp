// https://codeforces.com/contest/1762/problem/A
// https://codeforces.com/problemset/problem/1762/A

#include <bits/stdc++.h>
using namespace std;
int arr[51], numOp[51], t, n, a;
int main(){
    std::ios::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        int sumN = 0;
        for(int i = 0; i < n; i++){
            cin >> arr[i];
            sumN += arr[i];
            int num = arr[i];
            int op = 0;
            if(num %2 == 0){
                while(num%2 != 1){
                    num/=2;
                    op++;
                }
                numOp[i] = op;
            }else{
                while(num%2 != 0){
                    num/=2;
                    op++;
                }
                numOp[i] = op;
            }
        }
        if(sumN % 2 == 0){
            cout << 0 << endl;
        }else{
            int minOp = INT_MAX;
            for(int i = 0; i < n; i++){
                minOp = min(minOp, numOp[i]);
            }
            cout << minOp << endl;
        }
    }
}