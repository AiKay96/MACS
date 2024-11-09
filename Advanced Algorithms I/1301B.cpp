// https://codeforces.com/contest/1301/problem/B
// https://codeforces.com/problemset/problem/1301/B

#include<bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int k = 0; k < t; k++){
        int n;
        cin >> n;
        vector<int> vec;
        for(int i = 0; i < n; i++){
            int a;
            cin >> a;
            vec.push_back(a);
        }
        vector<int> v;
        vector<int> been(n, false);
        for(int i = 0; i < n; i++){
            if(vec[i] == -1){
                if(i >= 1 && vec[i-1]!= -1 && !been[i-1]){
                    v.push_back(vec[i-1]);
                    been[i-1] = true;
                }
                if(i < n - 1 && vec[i+1] != -1 && !been[i+1]){
                    v.push_back(vec[i+1]);
                    been[i+1] = true;
                }
            }
        }
        int mini = INT_MAX;
        int maxi = INT_MIN;
        for(int i = 0; i < v.size(); i++){
            mini = min(mini, v[i]);
            maxi = max(maxi, v[i]);
        }
        int ka = (mini + maxi) / 2;
        for(int i = 0; i < n; i++)
            if(vec[i] == -1)
                vec[i] = ka;
        int m = INT_MIN;
        for(int i = 1; i < n; i++)
            m = max(abs(vec[i] - vec[i-1]), m);
        cout << m << " " << ka << endl;
    }
}