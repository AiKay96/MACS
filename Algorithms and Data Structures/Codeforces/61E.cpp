// https://codeforces.com/contest/61/problem/E
// https://codeforces.com/problemset/problem/61/E

#include <bits/stdc++.h>
using namespace std;

int n, num[1000001], fenwick[2][1000001], ans[2][1000001];
pair<int, int> nums[1000001];
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> nums[i].first;
        nums[i].second = i;
    }
    sort(nums, nums + n);
    for(int i = 0; i < n; i++)
        num[i] = nums[i].second + 1;
    for(int i = 0; i < n; i++){
        //update sum
        int sum = 0;
        int ind = num[i];
        while(ind > 0){
            sum += fenwick[0][ind];
            ind -= (ind & -ind);
        }
        ind = n;
        int fullSum = 0;
        while(ind > 0){
            fullSum += fenwick[0][ind];
            ind -= (ind & -ind);
        }
        ans[0][i] = fullSum - sum;
        //update tree
        ind = num[i];
        while(ind <= n){
            fenwick[0][ind] += 1;
            ind += (ind & -ind);
        }
    }
    for(int i = n-1; i >= 0; i--){
        //update sum
        int sum = 0;
        int ind = num[i];
        while(ind > 0){
            sum += fenwick[1][ind];
            ind -= (ind & -ind);
        }
        ans[1][i] = sum;
        //update tree
        ind = num[i];
        while(ind <= n){
            fenwick[1][ind] += 1;
            ind += (ind & -ind);
        }
    }
    long long answer = 0;
    for(int i = 1; i < n; i++)
        answer += (long long)ans[0][i] * (long long)ans[1][i];
    cout << answer << endl;
}