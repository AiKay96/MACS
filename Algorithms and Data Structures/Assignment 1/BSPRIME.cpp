// https://www.spoj.com/problems/BSPRIME/

#include <bits/stdc++.h>
using namespace std;
int num[101865020], pnum[5862600], primesLength[5862600], primesOnes[5862600];
int k = 1, j, i, t, n, h;

int main(){
    num[2] = 2;
    pnum[k] = 2;
    primesLength[k] = primesLength[k-1] + (32 - __builtin_clz(2));
    primesOnes[k] = primesOnes[k-1] + __builtin_popcount(2);
    k++;
    for(i = 3; i <= 101865020; i += 2){
        if(num[i] == 0){
            num[i] = i;
            pnum[k] = i;
            primesLength[k] = primesLength[k-1] + (32 - __builtin_clz(i));
            primesOnes[k] = primesOnes[k-1] + __builtin_popcount(i);
            k++;
        }
        for(j = 0; ; j++){
            if ( (j==k) || ((i*pnum[j])>101865020) || (pnum[j]>num[i]) ) break;
            num[i*pnum[j]] = pnum[j];
        }
    }
    cin >> t;
    for(h = 0; h < t; h++){
        cin >> n;
        int left = 0;
        int right = 5862595;
        int mid;
        while(left < right){
            mid = (left + right) / 2;
            if(n > primesLength[mid])
                left = mid + 1;
            else
                right = mid;
        }
        if(n == primesLength[left]){
            cout << primesOnes[left] << endl;
            continue;
        }
        int tmp = primesLength[left];
        int ans = primesOnes[left];
        int primeNum = pnum[left];
        while(tmp > n){
            tmp--;
            ans -= primeNum % 2;
            primeNum /= 2;
        }
        cout << ans << endl;
    }
}