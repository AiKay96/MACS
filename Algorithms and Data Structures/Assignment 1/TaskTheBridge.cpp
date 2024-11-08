// https://szkopul.edu.pl/problemset/problem/QOI_596ZIIk4CbamVRXVvbAI/site/?key=statement

#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> times;
long long time(int ind);

int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        times.push_back(a);
    }
    cout << time(n-1) << endl;
}
long long time(int ind){
    if(ind < 3){
        if(ind == 2)
            return (long long)(times[0] + times[1] + times[2]);
        if(ind == 1)
            return (long long)times[1];
        return times[0];
    }
    int a = times[0];
    int b = times[1];
    int c = times[ind-1];
    int d = times[ind];
    return (long long)min(2*a + c + d, a + 2*b + d) + time(ind - 2);
}