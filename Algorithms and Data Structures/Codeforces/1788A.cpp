// https://codeforces.com/contest/1788/problem/A
// https://codeforces.com/problemset/problem/1788/A

#include <bits/stdc++.h>
using namespace std;
int n, m, a, b;
int main(){
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        int wagma[n];
        for(int i = 0; i < n; i++){
            cin >> a;
            wagma[i] = a;
        }
        int counter= 0;
        for(int i = 0; i < n; i++){
            if(wagma[i] == 2)
                counter++;
        }
        if(counter % 2 == 0){
            counter /= 2;
            for(int i = 0; i < n; i++){
                if(wagma[i] == 2)
                    counter--;
                if(counter == 0){
                    cout << i+1 << endl;
                    break;
                }
            }
        }else{
            cout << -1 << endl;
        }
    }
}