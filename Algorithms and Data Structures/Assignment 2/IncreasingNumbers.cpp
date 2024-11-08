// https://www.spoj.com/problems/NDS/

#include <bits/stdc++.h>
using namespace std;
 
int t, n, k;
int main(){
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        int arr[n], dp[n];
        for(int i = 0; i < n; i++){
            cin >> arr[i];
            dp[i] = INT_MAX;
        }
        dp[0] = arr[0];
        for(int i = 1; i < n; i++){
            int left = 0;
            int right = n;
            while(left < right){
                int mid = (left + right) / 2;
                if(arr[i] > dp[mid])
                    left = mid + 1;
                else
                    right = mid;
            }
            dp[left] = arr[i];
        }
        cin >> k;
        if(k > n || k <= 0 || dp[k-1] == INT_MAX)
            cout << -1 << endl;
        else
            cout << dp[k-1] << endl;
    }
}
