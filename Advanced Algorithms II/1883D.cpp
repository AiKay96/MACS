// https://codeforces.com/contest/1883/problem/D
// https://codeforces.com/problemset/problem/1883/D

#include <bits/stdc++.h>
using namespace std;

int main() {
    multiset<int> left, right;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        char t;
        int l, r;
        cin >> t >> l >> r;
        if(t == '+'){
            left.insert(l);
            right.insert(r);
        } else {
            left.erase(left.find(l));
            right.erase(right.find(r));
        }
        
        if(right.size() == 0){
            cout << "NO" << endl;
            continue;
        }
            
        
        int leftest = *right.begin();
        int rightest = *(--left.end());
        if(leftest < rightest)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
       
    }
}