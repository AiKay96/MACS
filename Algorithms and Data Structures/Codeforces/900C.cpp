// https://codeforces.com/contest/900/problem/C
// https://codeforces.com/problemset/problem/900/C

#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<int> vec;
    vector<int> arr(n+1, 0);
    set<int> st;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        st.insert(a);
        vec.push_back(a);
        if(i > 0){
            set<int>::iterator ita = st.find(a);
            set<int>::iterator end = st.end();
            end--;
            ita++;
            if(ita == end)
                arr[*end]++;
        }
    }
    int num = arr[1];
    int ans = 1;
    for(int i = 2; i <= n; i++){
        if(arr[i] > num){
            ans = i;
            num = arr[i];
        }
    }
    int i = 1;
    int tempAns = INT_MAX;
    if(num == 0 || num == 1){
        while(i < n && vec[i] > vec[i - 1]){
            i++;
            if(i == n)
                tempAns = 1;
        }
        while(i < n){
            tempAns = min(tempAns, vec[i]);
            i++;
        }
        ans = tempAns;
        if(n == 1)
            ans = 1;
    }
    cout << ans << endl;
}