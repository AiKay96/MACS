// https://codeforces.com/contest/1736/problem/C1
// https://codeforces.com/problemset/problem/1736/C1

#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        int n;
        cin >> n;
        vector<int> nums;
        for(int i = 0; i < n; i++){
            int a;
            cin >> a;
            nums.push_back(a);
        }
        long long dp[n];
        long long ans = 1;
        dp[0] = 1;
        for(int i = 1; i < n; i++){
            if(nums[i] > dp[i-1])
                dp[i] = dp[i-1] + 1;
            else
                dp[i] = nums[i];
            ans+=dp[i];
        }
        cout << ans << endl;
    }
}