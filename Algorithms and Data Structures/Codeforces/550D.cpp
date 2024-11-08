// https://codeforces.com/contest/550/problem/D
// https://codeforces.com/problemset/problem/550/D

#include <bits/stdc++.h>
using namespace std;
int t, n, m, k, a, b, c, d;

void buildUp(int start){
    int counter = (n - 1) / 2;
    for(int i = start; i <= start + n; i++){
        for(int j = i + 1; j <= start + n; j++){
            if(i %2 == 1 && j == i + 1 && counter != 0){
                cout << i << " " << a << endl;
                cout << j << " " << a << endl;
                counter--;
            }else{
                cout << i << " " << j << endl;
            }
        }
    }
}

int main(){
    cin >> n;
    if(n % 2 == 0){
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    if(n == 1){
        cout << "2 1" << endl;
        cout << "1 2" << endl;
        return 0;
    }
    int vs = (n + 2)*2;
    int es = vs*n/2;
    cout << vs << " " << es << endl;
    cout << "1 2" << endl;
    a = 1;
    buildUp(3);
    a = 2;
    buildUp(4+n);
}