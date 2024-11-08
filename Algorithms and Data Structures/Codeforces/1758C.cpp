// https://codeforces.com/contest/1758/problem/C
// https://codeforces.com/problemset/problem/1758/C

#include <bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    for(int h = 0; h < n; h++){
        int m, start;
        cin >> m >> start;
        if(m % start == 0){
            int tmp = start;
            vector<int> v;
            int arr[m+1];
            for(int i = 1; i <= m; i++)
                arr[i] = i;
            arr[1] = start;
            arr[m] = 1;
            int oldnewu = tmp;
            for(int i = 1; i <= m/start; i++){
                int newu = tmp*i;
                if(m % newu == 0 && newu % oldnewu == 0){
                    v.push_back(newu);
                    oldnewu = newu;
                }
            }
            for(int i = 1; i < v.size(); i++){
                arr[v[i-1]] = v[i];
            }
            for(int i = 1; i <= m; i++)
                cout << arr[i] << " ";
            cout << endl;
        }else{
            cout << -1 << endl;
        }
    }
}