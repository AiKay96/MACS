// https://www.spoj.com/problems/OHANIBTR/

#include <bits/stdc++.h>
using namespace std;
 
int t, n, arr[100001], parents[100001], roots[100001];
void findRoots(){
    int powN = 1;
    int duplicateN = 1;
    int tmpDuplicateN = 1;
    int tmpRaise = 1;
    for(int i = 0; i < 100000; i++){
        if(tmpDuplicateN == 0){
            roots[i] = roots[i-1] + 1;
            tmpRaise--;
            if(tmpRaise == 0){
                powN *= 2;
                duplicateN = powN / 2;
                tmpDuplicateN = duplicateN;
            }
        }else{
            roots[i] = powN;
            tmpDuplicateN--;
            tmpRaise = powN;
        }
    }
}
int findParents(int left, int right){
    if(left > right)
        return -1;
    int length = right - left;
    int root = left + roots[length] - 1;
    int leftChild = findParents(left, root - 1);
    if(leftChild != -1)
        parents[leftChild] = root;
    int rightChild = findParents(root + 1, right);
    if(leftChild != -1)
        parents[rightChild] = root;
    return root;
}
void coutParents(int n){
    for(int i = 0; i <= n; i++){
        if(parents[i] == 0)
            parents[i] = -1;
        else
            parents[i] = arr[parents[i]];
        if(i < n)
            cout << parents[i] << " ";
        else
            cout << parents[i];
    }
    cout << endl;
}
void longestIncreasingSubsequence(int n){
    vector<int> dp(n, INT_MAX);
    dp[0] = arr[0];
    int ans = 0;
    for(int i = 1; i < n; i++){
        int right = i;
        int left = 0;
        while(right > left){
            int mid = (left + right) / 2;
            if(arr[i] > dp[mid])
                left = mid + 1;
            else
                right = mid;
            
        }
        dp[left] = arr[i];
        ans = max(ans, left);
    }
    cout << "Minimum Move: " << n - ans - 1 << endl;
}
void renewArrays(int n){
    for(int i = 0; i < n; i++){
        parents[i] = 0;
        arr[i] = 0;
    }
}
int main(){
    findRoots();
    cin >> t;
    for(int h = 0; h < t; h++){
        cout << "Case " << h+1 << ":" << endl;
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> arr[i];
        longestIncreasingSubsequence(n);
        sort(arr, arr + n);
        findParents(0, n-1);
        coutParents(n-1);
        renewArrays(n);
    }
}
