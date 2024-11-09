// https://codeforces.com/contest/26/problem/B
// https://codeforces.com/problemset/problem/26/B

#include<bits/stdc++.h>
using namespace std;
vector<int> v[200001];
int main() {
    ios_base::sync_with_stdio(false);
    string s;
    cin >> s;
    int counter = 0;
    int ln = 0;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '('){
            counter++;
        }else{
            counter--;
            if(counter >= 0)
                ln++;
            counter = max(0, counter);
        }
    }
    cout << ln*2 << endl;
}