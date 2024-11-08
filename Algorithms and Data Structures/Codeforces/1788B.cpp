// https://codeforces.com/contest/1788/problem/B
// https://codeforces.com/problemset/problem/1788/B

#include <bits/stdc++.h>
using namespace std;
long long n, m, a, b;
int main(){
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        if(n % 2 == 0){
            cout << n/2 << " " << n/2 << endl;
            continue;
        }
        string s = to_string(n);
        string s1 = "";
        string s2 = "";
        int prioriteti = 1;
        for(int i = 0; i < s.length(); i++){
            int curr = s[i] - '0';
            if(curr % 2 == 0){
                char a = '0';
                a += curr/2;
                s1 += a;
                s2 += a;
            }else{
                char a = '0';
                a += curr/2;
                if(prioriteti == 1){
                    s1 += a;
                    a++;
                    s2 += a;
                    prioriteti = 2;
                }else{
                    s2 += a;
                    a++;
                    s1 += a;
                    prioriteti = 1;
                }
            }
        }
        int ans1 = 0;
        for(int i = 0; i< s1.length(); i++){
            ans1 *= 10;
            ans1 += s1[i] - '0';
        }
        int ans2 = 0;
        for(int i = 0; i< s2.length(); i++){
            ans2 *= 10;
            ans2 += s2[i] - '0';
        }
        cout << ans1 << " " << ans2 << endl;
    }
}