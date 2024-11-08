// https://codeforces.com/contest/1722/problem/C
// https://codeforces.com/problemset/problem/1722/C

#include <bits/stdc++.h>
using namespace std;
int main(){
  int t;
  cin >> t;
  for(int a = 0; a < t; a++){
    int n;
    cin >> n;
    
    vector<vector<int> > points;
    map<string, pair<int, int> > mp;
    for(int i = 0; i < 3; i++){
        vector<int> tmp;
        for(int j = 0; j < n; j++){
            string s;
            cin >> s;
            if(mp.count(s) == 1){
                if(i == 1){
                    mp[s].second = j;
                    tmp.push_back(1);
                    points[0][mp[s].first] = 1;
                }else if(i == 2){
                    if(mp[s].first != -1 && mp[s].second != -1){
                        tmp.push_back(0);
                        points[0][mp[s].first] = 0;
                        points[1][mp[s].second] = 0;
                    }else if(mp[s].first != -1 && mp[s].second == -1){
                        tmp.push_back(1);
                        points[0][mp[s].first] = 1;
                    }else if(mp[s].first == -1 && mp[s].second != -1){
                        tmp.push_back(1);
                        points[1][mp[s].second] = 1;
                    }
                }
            }else{
                tmp.push_back(3);
                pair<int, int > p;
                if(i == 0){
                   p.first = j;
                    p.second = -1;
                    mp[s] = p; 
                }else if(i == 1){
                    
                    p.first = -1;
                    p.second = j;
                    mp[s] = p;
                }
            }
        }
        points.push_back(tmp);
    }
    int ans1 = 0;
    for(int j = 0; j < n; j++)
        ans1 += points[0][j];
    int ans2 = 0;
    for(int j = 0; j < n; j++)
        ans2 += points[1][j];
    int ans3 = 0;
    for(int j = 0; j < n; j++)
        ans3 += points[2][j];
    cout << ans1 << " " << ans2 << " " << ans3 << endl;
  }
}