// https://codeforces.com/contest/652/problem/B
// https://codeforces.com/problemset/problem/652/B

#include <bits/stdc++.h>
using namespace std;
int factorial[100001];
int main(){
    int n;
    cin >> n;
    vector<int> v;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        v.push_back(a);
    }
    sort(v.begin(), v.end());
    for(int i = 2; i < n; i+=2){
        int tmp = v[i];
        v[i] = v[i-1];
        v[i-1] = tmp;
    }
    for(int i = 0; i < n; i++)
        cout << v[i] << " ";
    cout << endl;
}