// https://codeforces.com/contest/59/problem/C
// https://codeforces.com/problemset/problem/59/C

#include<bits/stdc++.h>
using namespace std;
int n;
bool anban[27];
int findBiggest(){
    int biggest = -1;
    for(int i = n-1; i >= 0; i--){
        if(!anban[i]){
            biggest = i;
            break;
        }
    }
    return biggest;
}
int main(){
    ios::sync_with_stdio(false);
    cin >> n;
    string s;
    cin >> s;
    for(int i = 0; i < s.length(); i++){
        if(s[i] != '?'){
            anban[s[i] -'a'] = true;
        }
    }
    string ans = s;
    bool bley = false;
    for(int i = (s.length() - 1) / 2; i >= 0; i--){
        if(s[i] == '?'){
            if(s[s.length() - 1 - i] == '?'){
                int ind = findBiggest();
                if(ind == -1){
                    ans[i] = 'a';
                    ans[s.length() - 1 - i] = 'a';
                }else{
                    ans[i] = 'a' + ind;
                    ans[s.length() - 1 - i] = 'a' + ind;
                    anban[ind] = true;
                }
            }else{
                ans[i] = s[s.length() - 1 - i];
            }
        }else{
            if(s[s.length() - 1 - i] == '?'){
                ans[s.length() - 1 - i] = s[i];
            }else{
                if(s[s.length() - 1 - i] != s[i]){
                    bley = true;
                    break;
                }
            }
        }
    }
    int count = 0;
    for(int i = 0; i < 27; i++){
        if(anban[i])
            count++;
        else
            break;
    }
    if(count != n)
        bley = true;
    if(bley){
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    cout << ans << endl;
}