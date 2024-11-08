// https://codeforces.com/contest/1767/problem/B
// https://codeforces.com/problemset/problem/1767/B

#include <bits/stdc++.h>
using namespace std;
int t, n, a, b;
int main(){
    std::ios::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        vector<int> vec;
        cin >> n;
        cin >> a;
        int start = a;
        for(int i = 1; i < n; i++){
            cin >> a;
            if(a > start)
                vec.push_back(a);
        }
        sort(vec.begin(), vec.end());
        int startInd = 0;
        while(startInd < vec.size()){
            start = (vec[startInd] + start + 1)/2;
            startInd++;
            while(startInd < vec.size() && start >= vec[startInd]){
                startInd++;
            }
        }
        cout << start << endl;
    }
}