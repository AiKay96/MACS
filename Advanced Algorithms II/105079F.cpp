// https://codeforces.com/gym/105079/problem/F
// https://codeforces.com/problemset/gymProblem/105079/F

#include<bits/stdc++.h>
using namespace std;
 
 
int main() {
    long long t;
    cin >> t;
    for(int k = 0; k < t; k++){
        long long n;
        cin >> n;
        
        long long arr[n+1];
        map<long long, vector<long long>> delindex;
        
        for(long long i = 1 ; i <=n;i++){
            cin >> arr[i];
            delindex[arr[i]].push_back(i);
        }
        
        long long ind = 0;
        long long ans = 0;
        for (auto cupcake : delindex){
            vector<long long> vec = cupcake.second;
            long long first = vec[0];
            long long last = vec[vec.size()-1];
            if (ind < first){
                ans += (last - ind);
                ind = last;
            }else{
                ans += (n-ind);
                long long jmp;
                for (int i =0; i < vec.size(); i++)
                    if(vec[i] < ind)
                        jmp = vec[i];
                ans += jmp;
                ind = jmp;
            }
        }
        cout << ans - 1 << endl;
    }
}