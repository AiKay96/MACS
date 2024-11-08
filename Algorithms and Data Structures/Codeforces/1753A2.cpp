// https://codeforces.com/contest/1753/problem/A2
// https://codeforces.com/problemset/problem/1753/A2

#include <bits/stdc++.h>
using namespace std;
int t, n;
int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        int arr[n];
        int prevInd = 0;
        vector<pair<int, int> > vec;
        for(int i = 0; i < n; i++){
            cin >> arr[i];
            if(arr[i] != 0){
                vec.push_back({i, i - prevInd});
                prevInd = i;
            }
        }
        vector<pair<int, int> > v;
        int ind = 1;
        if(vec.size() % 2 == 0){
            for(int i = 0; i < vec.size(); i+= 2){
                if(ind <= vec[i].first){
                    v.push_back({ind, vec[i].first});
                    ind == vec[i].first + 1;
                }
                if(arr[vec[i].first] == arr[vec[i+1].first]){
                    if(vec[i+1].second % 2 == 1){
                        v.push_back({vec[i].first + 1, vec[i+1].first + 1});
                        ind = vec[i+1].first + 2;
                    }else{
                        v.push_back({vec[i].first + 1, vec[i].first + 1});
                        v.push_back({vec[i].first + 2, vec[i+1].first + 1});
                        ind = vec[i+1].first + 2;
                    }
                }else{
                    v.push_back({vec[i].first + 1, vec[i].first + 1});
                    if(vec[i].first + 2 <= vec[i+1].first)
                        v.push_back({vec[i].first + 2, vec[i+1].first});
                    v.push_back({vec[i+1].first + 1, vec[i+1].first + 1});
                    ind = vec[i+1].first + 2;
                }
            }
            if(ind <= n)
                v.push_back({ind, n});
            cout << v.size() << endl;
            for(int i = 0; i < v.size(); i++){
                cout << v[i].first << " " << v[i].second << endl;
            }
        }else{
            cout << -1 << endl;
        }
    }
}