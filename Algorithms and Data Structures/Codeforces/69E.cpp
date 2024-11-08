// https://codeforces.com/contest/69/problem/E
// https://codeforces.com/problemset/problem/69/E

#include <bits/stdc++.h>
using namespace std;
int main(){
    int n, k;
    cin >> n >> k;
    set<int> st;
    map<int, int> mp;
    int arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        mp[arr[i]] = 0;
    }
    for(int i = 0; i < k-1; i++){
        mp[arr[i]]++;
        if(mp[arr[i]] == 1)
            st.insert(arr[i]);
        else
            st.erase(arr[i]);
    }
    for(int i = k-1; i < n; i++){
        mp[arr[i]]++;
        if(mp[arr[i]] == 1)
            st.insert(arr[i]);
        else
            st.erase(arr[i]);
        if(st.size() == 0)
            cout << "Nothing" << endl;
        else{
            set<int>::iterator it = st.end();
            it--;
            cout << *it << endl;
        }
        mp[arr[i-k+1]]--;
        if(mp[arr[i-k+1]] == 1)
            st.insert(arr[i-k+1]);
        else
            st.erase(arr[i-k+1]);
    }
}