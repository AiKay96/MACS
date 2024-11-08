// https://codeforces.com/contest/253/problem/B
// https://codeforces.com/problemset/problem/253/B

#include <bits/stdc++.h>
using namespace std;
int main(){
    ifstream readfile("input.txt");
	string N;
	getline(readfile, N);
	int n = 0;
	for (int i = 0; i < N.size(); i++){
		n *= 10;
		n += (N[i] - '0');
	}
	vector<int> nums;
	getline(readfile, N);
	int x = 0;
	for (int i = 0; i < N.size(); i++){
		if (N[i] == ' '){
			nums.push_back(x);
			x = 0;
		}
		else {
			x *= 10;
			x += (N[i] - '0');
		}
	}
	nums.push_back(x);
    sort(nums.begin(), nums.end());
    int begin = 1;
    int ans = INT_MAX;
    for(int i = 0; i < n; i++){
        int minimal = nums[i];
        int l = begin;
        int r = n;
        while(l < r){
            int mid = (l + r) / 2;
            if(nums[mid] > minimal*2)
                r = mid;
            else
                l = mid + 1;
        }
        int begin = l;
        ans = min(ans, i + n - l);
        if(i > ans)
            break;
    }
    ofstream ansfile;
	ansfile.open("output.txt");
	ansfile << ans << endl;
	ansfile.close();
}