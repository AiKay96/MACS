// https://codeforces.com/gym/105079/problem/G
// https://codeforces.com/problemset/gymProblem/105079/G

#include <bits/stdc++.h>
using namespace std;

int main() {
    multiset<long long> st;
    long long n;

    cin >> n;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        st.insert(a);
    }
    long long additions = 0;

    for (int i = 0; i < n; i++) {
        long long b;
        cin >> b;
        additions += b;

        long long best = *st.rbegin();
        st.erase(st.find(best));
        
        best += additions;
        best -= best / 2;
        best -= additions;
        
        st.insert(best);
    }

    long long sum = 0;
    for (auto it = st.begin(); it != st.end(); ++it) {
            sum += *it + additions;
        }
    cout << sum;
}