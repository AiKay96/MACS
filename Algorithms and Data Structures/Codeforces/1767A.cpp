// https://codeforces.com/contest/1767/problem/A
// https://codeforces.com/problemset/problem/1767/A

#include <bits/stdc++.h>
using namespace std;
int t, n, a, b;
int arrA[4], arrB[4];
bool isMart(int x, int y, int a, int b){
    if(x == a || y == b)
        return true;
    return false;
}
int main(){
    std::ios::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        for(int i = 1; i < 4; i++){
            cin >> a >> b;
            arrA[i] = a;
            arrB[i] = b;
        }
        bool ans1 = isMart(arrA[1],arrB[1], arrA[2], arrB[2]);
        bool ans2 = isMart(arrA[2],arrB[2], arrA[3], arrB[3]);
        bool ans3 = isMart(arrA[1],arrB[1], arrA[3], arrB[3]);
        if(ans1){
            if(ans3 || ans2)
                cout << "NO" << endl;
            else
                cout << "YES" << endl;
        }else{
            if(ans2 && ans3)
                cout << "NO" << endl;
            else
                cout << "YES" << endl;
        }
    }
}