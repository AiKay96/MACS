// https://codeforces.com/contest/1799/problem/C
// https://codeforces.com/problemset/problem/1799/C

#include <bits/stdc++.h>
using namespace std;
 
int main(){
    int t;
    cin >> t;
    for(int q = 0; q < t; q++){
        string s;
        cin >> s;
        string l = "";
        string r = "";
        vector<int> v(26, 0);
        for(int i = 0; i < s.length(); i++)
            v[s[i] - 'a']++;
        char bg = 'a';
        for(int i = 0; i < s.length(); i++)
            if(s[i] > bg)
                bg = s[i];
        string curr = "";
        for(char c = 'a'; c <= 'z'; c++){
            if(v[c - 'a'] == 0) continue;
            if(curr.size() != 0 && c != bg){
                l += curr[0];
                for(char a = c; a <= 'z'; a++)
                    for(int i = 0; i < v[a - 'a']; i++)
                        r += a;
                curr = "";
                break;
            }
            if(v[c - 'a'] % 2 != 0){
                for(int i = 0; i < v[c - 'a'] / 2; i++)
                    l += c;
                for(int i = 0; i < v[c - 'a'] / 2; i++)
                    r += c;
                curr += c;
            }else{
                for(int i = 0; i < v[c - 'a'] / 2; i++)
                    l += c;
                for(int i = 0; i < v[c - 'a'] / 2; i++)
                    r += c;
            }
        }
        l += curr;
        string tmp = "";
        for(int i = r.length() - 1; i >= 0; i--)
            tmp += r[i];
        s = l + tmp;
        tmp = "";
        for(int i = s.length() - 1; i >= 0; i--)
            tmp += s[i];
        cout << max(s, tmp) << endl;
    }
}