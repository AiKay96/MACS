// https://codeforces.com/contest/1737/problem/A
// https://codeforces.com/problemset/problem/1737/A

#include <bits/stdc++.h>
using namespace std;
int t;
string s;
int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        int n, c;
        cin >> n >> c;
        int k = n/c;
        cin >> s;
        set<char> st;
        map<char, int> mp;
        for(int i = 0; i < s.length(); i++){
            st.insert(s[i]);
            mp[s[i]]++;
        }
        string ans = "";
        char maxChar = 'a' + k;
        for(int i = 0; i < c; i++)
            ans += 'a';
        set<char>::iterator it = st.begin();
        while(!st.empty()){
            char curr = *it;
            int numChar = min(mp[curr], (int)ans.length());
            for(int i = 0; i < numChar; i++){
                if(curr == ans[i] && curr != maxChar){
                    char tmp = curr;
                    tmp++;
                    ans[i] = tmp;
                }
            }
            it++;
            st.erase(curr);
        }
        cout << ans << endl;
    }
}