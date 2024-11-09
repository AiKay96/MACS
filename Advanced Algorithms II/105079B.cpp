// https://codeforces.com/gym/105079/problem/B
// https://codeforces.com/problemset/gymProblem/105079/B

#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) 
        return false;
    for (int i = 2; i < n; i++) 
        if (n % i == 0) 
            return false;
    return true;
}

int main() {
    int n;
    cin >> n;
    while(isPrime(n)){
        n++;
    }
    cout << n << endl;
}