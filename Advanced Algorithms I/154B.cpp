// https://codeforces.com/contest/154/problem/B
// https://codeforces.com/problemset/problem/154/B

#include<bits/stdc++.h>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    bool onoff[n+1];
    int arr[n+1];
    for(int i = 1; i <= n; i++){
        arr[i] = 0;
        onoff[i] = false;
    }
    for(int i = 0; i < m; i++){
        char s;
        cin >> s;
        if(s == '+'){
            int c;
            cin >> c;
            if(onoff[c]){
                cout << "Already on" << endl;
                continue;
            }
            int conf = 0;
            for(int j = 2; j <= sqrt(c); j++){
                if(c % j == 0){
                    if(arr[j] != 0 || arr[c/j] != 0){
                        conf = j;
                        if(arr[j] == 0)
                            conf = c/j;
                        break;
                    }
                }
            }
            if(arr[c] != 0 && c != 1)
                conf = c;
            if(conf == 0){
                for(int j = 2; j <= sqrt(c) + 1; j++){
                    if(c % j == 0){
                        arr[j] = c;
                        arr[c/j] = c;
                    }
                }
                arr[c] = c;
                onoff[c] = true;
                cout << "Success" << endl;
            }else{
                cout << "Conflict with " << arr[conf] << endl;
            }
        }else{
            int c;
            cin >> c;
            if(onoff[c]){
                 for(int j = 2; j <= sqrt(c) + 1; j++){
                    if(c % j == 0){
                        arr[j] = 0;
                        arr[c/j] = 0;
                    }
                }
                arr[c] = 0;
                onoff[c] = false;
                cout << "Success" << endl;
            }else{
                cout << "Already off" << endl;
            }
        }
    }
}