// https://codeforces.com/contest/35/problem/C
// https://codeforces.com/problemset/problem/35/C

#include <bits/stdc++.h>
using namespace std;
int n, m, k, kx[10], ky[10], mins[2001][2001];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> n >> m >> k;
    for(int i = 0; i < k; i++){
        cin >> kx[i] >> ky[i];
        kx[i]--;
        ky[i]--;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int mint = INT_MAX;
            for(int h = 0; h < k; h++)
                mint = min(mint, abs(kx[h] - i) + abs(ky[h] - j));
            mins[i][j] = mint;
        }
    }
    int maxt = -1;
    int maxx,maxy;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mins[i][j] > maxt){
                maxt = mins[i][j];
                maxx = i+1;
                maxy = j+1;
            }
        }
    }
	cout << maxx << " " << maxy << endl;
}