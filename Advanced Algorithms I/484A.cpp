// https://codeforces.com/contest/484/problem/A
// https://codeforces.com/problemset/problem/484/A

#include <bits/stdc++.h>
using namespace std;
 
int main(){
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        long long l, r;
        cin >> l >> r;
        long long ll = l;
        long long rr = r;
        int lb[64];
        int rb[64];
        for(int i = 0; i < 64; i++){
            lb[i] = 0;
            rb[i] = 0;
        }
        int ind = 63;
        while(true){
            lb[ind] = l % 2;
            if(l <= 1)
                break;
            l/=2;
            ind--;
        }
        ind = 63;
        while(true){
            rb[ind] = r % 2;
            if(r <= 1)
                break;
            r/=2;
            ind--;
        }
        ind = 0;
        while(ind < 64 && lb[ind] == rb[ind])
            ind++;
        bool ertebi = true;
        for(int i = ind; i < 64; i++)
            if(rb[i] != 1)
                ertebi = false;
        if(ertebi){
            cout << rr << endl;
            continue;
        }
        for(int i = ind + 1; i < 64; i++)
            lb[i] = 1;
        long long num = 1;
        for(int i = 0; i < 64; i++){
            num *= 2;
            num += lb[i];
        }
        cout << num << endl;
    }
}