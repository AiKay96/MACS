// https://codeforces.com/contest/1758/problem/B
// https://codeforces.com/problemset/problem/1758/B

#include <bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> m;
        if(m%2 == 1){
            for(int j = 0; j < m; j++)
                cout << "1 ";
            cout << endl;
        }else{
            cout << "2 6 ";
            m-=2;
            for(int j = 0; j < m; j++)
                cout << "4 ";
            cout << endl;
        }
    }
}