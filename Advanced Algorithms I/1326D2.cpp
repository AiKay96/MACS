// https://codeforces.com/contest/1326/problem/D2
// https://codeforces.com/problemset/problem/1326/D2

#include <bits/stdc++.h>
using namespace std;

vector<int> manacher_odd(string str) {
    int r = 0, c = 0, n = str.size();
    vector<int> v(n + 3);
    for (int i = 0; i < n; i ++) {
        if (i < r) {
            v[i] = min (r - i, v[2 * c - i]);
        }

        while (i >= v[i] && i + v[i] < n && str[i + v[i]] == str[i - v[i]]) {
            v[i] ++;
        }

        if (i + v[i] > r) {
            c = i;
            r = i + v[i];
        }
    }
    return v;
}

int main(){
	int t;
	cin >> t;
	for(int q = 0; q < t; q++){
	    string s;
	    cin >> s;
	    int l = 0;
	    int r = s.length() - 1;
	    while(l < r && s[l] == s[r]){
	        l++;
	        r--;
	    }
	    string str = s.substr(l, r - l + 1);
	    string temp = str;
	    string tmp = "";
	    int sz = str.size();
	    for(int i = 0; i < sz; i++){
	        tmp += str[i];
	        if(i != sz - 1)
	            tmp += '.';
	    }
	    str = tmp;
	    string ans = "";
        int maxi = 0;
		vector<int> v = manacher_odd(str);
		for(int i = 0; i <= sz; i++)
			if(v[i - 1] == i)
			    maxi = max(maxi,i);
		if(ans.length() < maxi)
			ans = temp.substr(0, maxi);
		string tempo = "";
		for(int i = str.length() - 1; i >= 0; i--)
		    tempo += str[i];
		str = tempo;
		tempo = "";
		for(int i = temp.length() - 1; i >= 0; i--)
		    tempo += temp[i];
		temp = tempo;
		maxi = 0;
		v = manacher_odd(str);
		for(int i = 0; i <= sz; i++)
			if(v[i - 1] == i)
			    maxi = max(maxi,i);
		if(ans.length() < maxi)
			ans = temp.substr(0, maxi);
		tempo = "";
		for(int i = str.length() - 1; i >= 0; i--)
		    tempo += str[i];
		str = tempo;
		tempo = "";
		for(int i = temp.length() - 1; i >= 0; i--)
		    tempo += temp[i];
		temp = tempo;
		string start = s.substr(0,l);
		string end = "";
		for(int i = start.length() - 1; i >= 0; i--)
		    end += start[i];
		cout << start + ans + end << endl;
	}
}