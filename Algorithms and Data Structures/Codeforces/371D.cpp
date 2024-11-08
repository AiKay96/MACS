// https://codeforces.com/contest/371/problem/D
// https://codeforces.com/problemset/problem/371/D

#include <bits/stdc++.h>
using namespace std;
int n, m, t, x;
int main(){
    ios_base::sync_with_stdio(false);
    cin >> n;
    int capacity[n];
    int currPos[n];
    set<pair<int, int> > st;
    for(int i = 0; i < n; i++){
        cin >> capacity[i];
        currPos[i] = 0;
        st.insert({i, 0});
    }
    cin >> m;
    for(int i = 0; i < m; i++){
        cin >> t >> n;
        n--;
        set<pair<int, int> >::iterator it = st.lower_bound({n, 0});
        if(t == 1){
            cin >> x;
            while(it != st.end()){
                pair<int, int> curr = *it;
                int ind = curr.first;
                int currPosition = curr.second;
                if(currPosition + x < capacity[ind]){
                    currPos[ind] = currPosition + x;
                    st.insert({ind, currPos[ind]});
                }else{
                    currPos[ind] = capacity[ind];
                }
                st.erase(it++);
                x -= currPos[ind] - currPosition;
                if(x <= 0)
                    break;
            }
        }else{
            cout << currPos[n] << endl;
        }
    }
}