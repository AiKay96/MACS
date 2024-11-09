// https://codeforces.com/contest/1153/problem/C
// https://codeforces.com/problemset/problem/1153/C

#include<bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    string s;
    cin >> s;
    if(n %2 == 1){
        cout << ":(" << endl;
        return 0;
    }
    string ans;
    int gaxsna = n / 2;
    for(int i = 1; i < n; i++)
        if(s[i] == '(')
            gaxsna--;
    int counter = 0;
    if(s[0] == ')'){
        cout << ":(" << endl;
        return 0;
    }
    counter++;
    ans += '(';
    gaxsna--;
    bool dagverxa = false;
    for(int i = 1; i < n - 1; i++){
        if(s[i] == '?'){
            if(gaxsna > 0){
                counter++;
                ans+= '(';
                gaxsna--;
            }else if(counter - 1 > 0){
                counter--;
                ans += ')';
            }else{
                dagverxa = true;
                break;
            }
        }else{
            if(s[i] == '('){
                counter++;
                ans += '(';
            }else{
                if(counter - 1 > 0){
                    counter--;
                    ans += ')';
                }else{
                    dagverxa = true;
                    break;
                }
            }
        }
    }
    if(dagverxa){
        cout << ":(" << endl;
        return 0;
    }
    if(s[n-1] == '('){
        cout << ":(" << endl;
        return 0;
    }
    ans+= ')';
    counter--;
    if(counter == 0){
        cout << ans << endl;
    }else{
        cout << ":(" << endl;
    }
}