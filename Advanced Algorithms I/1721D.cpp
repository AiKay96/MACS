// https://codeforces.com/contest/1721/problem/D
// https://codeforces.com/problemset/problem/1721/D

#include<bits/stdc++.h>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        int n;
        cin >> n;
        int a[n], b[n];
        for(int i = 0; i < n; i++)
            cin >> a[i];
        for(int i = 0; i < n; i++)
            cin >> b[i];
        int mask = 0;
        for(int i = 31; i >= 0; i--){
            mask += 1 << i;
            vector<int> amask, bmask;
            for(int i = 0; i < n; i++)
                amask.push_back((a[i] ^ mask) & mask);
            for(int i = 0; i < n; i++)
                bmask.push_back(b[i] & mask);
            sort(amask.begin(), amask.end());
            sort(bmask.begin(), bmask.end());
            if(amask != bmask)
                mask -= 1 << i;
        }
        cout << mask << endl;
    }
}