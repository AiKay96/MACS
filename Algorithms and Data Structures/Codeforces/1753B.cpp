// https://codeforces.com/contest/1753/problem/B
// https://codeforces.com/problemset/problem/1753/B

#include <bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    set<int> st;
    map<int, int> mp;
    int n, x;
    cin >> n >> x;
    for(int i = 0; i < n; i++){
        int a;
        cin>> a;
        st.insert(a);
        mp[a]++;
    }
    set<int>::iterator it;
    while(!st.empty()){
        it = st.begin();
        int curr = *it;
        if(curr == x){
            cout << "Yes" << endl;
            return 0;
        }
        int num = mp[curr];
        curr++;
        if(num % curr == 0){
            mp[curr] += num/curr;
            st.insert(curr);
        }else{
            cout << "No" << endl;
            return 0;
        }
        st.erase(it++);
    }
    cout << "Yes" << endl;
}