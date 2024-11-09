// https://codeforces.com/gym/105079/problem/A
// https://codeforces.com/problemset/gymProblem/105079/A

#include <bits/stdc++.h>
using namespace std;
int arr[101];

int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        int a;
        cin >> a;
        arr[a]++;
    }
    for(int i = 1; i <= m; i++){
        if (arr[i] > 0){
            arr[i] = (arr[i] - 1) / 12 + 1;
        }
        cout << arr[i] << endl;
    }
}