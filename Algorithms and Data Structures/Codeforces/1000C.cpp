// https://codeforces.com/contest/1000/problem/C
// https://codeforces.com/problemset/problem/1000/C

#include <bits/stdc++.h>
using namespace std;
int main(){
    int k;
    cin >> k;
    vector<long long> arr(k + 1, 0);
    vector<pair<long long, int> > vc;
    for(int i = 0; i < k; i++){
        long long l, r;
        cin >> l >> r;
        vc.push_back({l, 0});
        vc.push_back({r, 1});
    }
    sort(vc.begin(), vc.end());
    int counter = 1;
    for(int i = 1; i < vc.size(); i++){
        arr[counter] += vc[i].first - vc[i-1].first;
        if(vc[i].second != vc[i-1].second){
            if(vc[i].second == 0)
                arr[counter]--;
            else
                arr[counter]++;
        }
            
        if(vc[i].second == 0)
            counter++;
        else
            counter--;
    }
    for(int i = 1; i <= k; i++)
        cout << arr[i] << " ";
    cout << endl;
}