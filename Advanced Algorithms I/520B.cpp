// https://codeforces.com/contest/520/problem/B
// https://codeforces.com/problemset/problem/520/B

#include<bits/stdc++.h>
using namespace std;
int numsteps;
void ukugma(int n, int target){
    if(n < 0)
        return;
    if(n == target)
        return;
    numsteps++;
    if(n % 2 == 0 && n > target){
        ukugma(n/2, target);
    }else{
        ukugma(n+1, target);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    int a, b;
    cin >> a >> b;
    numsteps = 0;
    ukugma(b, a);
    cout << numsteps << endl;
}