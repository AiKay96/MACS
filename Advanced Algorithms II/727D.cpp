// https://codeforces.com/contest/727/problem/D
// https://codeforces.com/problemset/problem/727/D

#include<bits/stdc++.h>
using namespace std;
int num[6];

string getStr(int ind){
    if(ind == 0)
        return "S";
    if(ind == 1)
        return "M";
    if(ind == 2)
        return "L";
    if(ind == 3)
        return "XL";
    if(ind == 4)
        return "XXL";
    return "XXXL";
}

int getInd(string s){
    if(s == "S")
        return 0;
    if(s == "M")
        return 1;
    if(s == "L")
        return 2;
    if(s == "XL")
        return 3;
    if(s == "XXL")
        return 4;
    return 5;
}
int main(){
  	ios_base::sync_with_stdio(false);
    for(int i = 0; i < 6; i++)
        cin >> num[i];
    int n;
    cin >> n; 
    pair<int, int> want[n];
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        int comma = -1;
        for(int j = 0; j < s.length(); j++){
            if(s[j] == ',')
                comma = j;
        }
        if(comma == -1){
            want[i] = {getInd(s), -1};
        }else{
            string s1 = s.substr(0, comma);
            string s2 = s.substr(comma + 1);
            want[i] = {getInd(s1), getInd(s2)};
        }
    }
    int given[n];
    for(int i = 0; i < n; i++)
        given[i] = 0;
    for(int i = 0; i < n; i++){
        if(want[i].second == -1){
            num[want[i].first]--;
            if(num[want[i].first] < 0){
                cout << "NO" << endl;
                return 0;
            }
            given[i] = 1;
        }
    }
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < n; j++){
            if(want[j].second != -1){
                if(given[j] == 0 && want[j].second == i && num[i] > 0){
                    //cout << "second" << endl;
                    //cout << j << " wants " << getStr(want[j].first) << endl;
                    num[i]--;
                    given[j] = 2;
                }
            }
        }
        for(int j = 0; j < n; j++){
            if(want[j].second != -1){
                if(given[j] == 0 && want[j].first == i && num[i] > 0){
                    //cout << "first" << endl;
                    //cout << j << " wants " << getStr(want[j].first) << endl;
                    num[i]--;
                    given[j] = 1;
                }
            }
        }
    }
    for(int i = 0; i< n; i++){
        if(given[i] == 0){
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    for(int i = 0; i < n; i++){
        if(given[i] == 1)
            cout << getStr(want[i].first) << endl;
        else
            cout << getStr(want[i].second) << endl;
    }
}