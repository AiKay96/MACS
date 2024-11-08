// https://codeforces.com/contest/372/problem/A
// https://codeforces.com/problemset/problem/372/A

#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<int> kangaroos;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        kangaroos.push_back(a);
    }
    sort(kangaroos.begin(), kangaroos.end());
    int visible = 0;
    int son = n/2 - 1;
    for(int i = n - 1; i >= n/2; i--){
        visible++;
        int mom = kangaroos[i];
        while(son >= 0 && kangaroos[son]*2 > mom){
            visible++;
            son--;
        }
        son--;
    }
    cout << visible << endl;
}