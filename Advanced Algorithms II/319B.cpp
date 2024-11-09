// https://codeforces.com/contest/319/problem/B
// https://codeforces.com/problemset/problem/319/B

#include<bits/stdc++.h>
using namespace std;
 
int arr[110000];
 
int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arr[i+1];
        
    int ans = 0;
    stack<int>st;
    for(int i = n; i > 0; i--){
        int step = 0;
        
        while(!st.empty() && arr[i] > st.top()){
            step++;
            st.pop();
            step = max(step, st.top());
            st.pop();
        }
        st.push(step);
        st.push(arr[i]);
        ans = max(ans, step);
        
    }
    cout<< ans <<endl;
}