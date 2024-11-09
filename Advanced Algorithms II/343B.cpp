// https://codeforces.com/contest/343/problem/B
// https://codeforces.com/problemset/problem/343/B

#include <bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cin >> s;
    stack<char> st;
    st.push('0');
    for(int i = 0; i < s.length(); i++){
        if(st.top() == s[i])
            st.pop();
        else
            st.push(s[i]);
    }
    if(st.size() == 1)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}