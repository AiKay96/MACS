// https://codeforces.com/gym/105079/problem/C
// https://codeforces.com/problemset/gymProblem/105079/C

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, R;
    cin >> n >> R;
    set<pair<int, int>> st;
    for(int i = 0; i < n; i++){
        int r, x, y;
        cin >> r >> x >> y;
        for (int i = -1*R; i <= R; i++){
            for (int j = -1*R; j <= R; j++){
                int xi = (x-i)*(x-i) + (y-j)*(y-j);
                if (xi <= r*r){
                    int yi = i*i + j*j;
                    if (yi <= R*R){
                        st.insert({i,j});
                    }
                }
            }
        }
    }
    cout << st.size();
}