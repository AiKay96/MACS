// https://codeforces.com/contest/1743/problem/B
// https://codeforces.com/problemset/problem/1743/B

#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        int n;
        cin >> n;
        int minN = 1;
        int maxN = n;
        vector<int> arr;
        while(minN < maxN){
            arr.push_back(minN);
            minN++;
            arr.push_back(maxN);
            maxN--;
        }
        arr.push_back(minN);
        for(int i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
}