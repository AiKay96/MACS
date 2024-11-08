// https://codeforces.com/contest/1795/problem/A
// https://codeforces.com/problemset/problem/1795/A

#include <bits/stdc++.h>
using namespace std;
int n, m;
int main(){
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n >> m;
        string s1, s2;
        cin >> s1 >> s2;
        for(int i = s2.length() - 1; i >= 0; i--)
            s1 += s2[i];
        int same = 0;
        for(int i = 1; i < s1.length(); i++)
            if(s1[i] == s1[i-1])
                same++;
        if(same <= 1)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}