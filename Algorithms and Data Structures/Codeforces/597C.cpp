// https://codeforces.com/contest/597/problem/C
// https://codeforces.com/problemset/problem/597/C

#include <bits/stdc++.h>
using namespace std;
 
long long n, k, fenwick[11][100001], nums[100001];
long long sum(int ind, int tree){
    long long s = 0;
    while(ind > 0){
        s += fenwick[tree][ind];
        ind -= (ind & -ind);
    }
    return s;
}
void update(int ind, int tree, long long value){
    while(ind <= n){
        fenwick[tree][ind] += value;
        ind += (ind & -ind);
    }
}
int main(){
    cin >> n >> k;
    for(int i = 0; i < n; i++)
        cin >> nums[i];
    for(int i = 0; i < n; i++){
        update(nums[i], 0, 1);
        for(int j = 1; j < 11; j++){
            long long s = sum(nums[i]-1, j-1);
            update(nums[i], j, s);
        }
    }
    cout << sum(n, k) << endl;
}