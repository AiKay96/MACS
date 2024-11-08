// https://codeforces.com/contest/1766/problem/B
// https://codeforces.com/problemset/problem/1766/B

#include <bits/stdc++.h>
using namespace std;
int main(){
    int t, n;
    string s;
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        cin >> s;
        if(s.length() < n){
            cout << "YES" << endl;
        }else{
            int ans = 1;
            set<string> st;
            string old = "";
            for(int i = 1; i < s.length(); i++){
                string hm = "";
                hm+=s[i-1];
                hm+=s[i];
                if(st.find(hm) == st.end()){
                    ans++;
                    st.insert(old);
                }
                old = hm;
                //cout << hm << " " << ans << endl;
            }
            //cout << ans << endl;
            if(ans < n)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }
}