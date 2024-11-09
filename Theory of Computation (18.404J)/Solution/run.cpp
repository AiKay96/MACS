#include<bits/stdc++.h>
using namespace std;

string inp, ans;
int n, a, t;
vector<vector<int> > transitions[36];
vector<bool> accepts;

int calculateCharIndex(char c){
    if(c >= 'a')
        return c - 'a';
    return 26 + c - '0';
}

void simulate(){
    queue<pair<int, int> > q;
    q.push({0, 0});
    while(!q.empty()){
        int stateind = q.front().first;
        int inputind = q.front().second;
        q.pop();
        
        if(inputind == inp.length())
            continue;
        
        int c = calculateCharIndex(inp[inputind]);    
        for(int i = 0; i < transitions[c][stateind].size(); i++){
            int nextstateind = transitions[c][stateind][i];
            if(accepts[nextstateind])
               ans[inputind] = 'Y';
            q.push({nextstateind, inputind + 1});
        }
    }
}

void initVectors(){
    accepts.clear();
    for(int i = 0; i < n; i++)
        accepts.push_back(false);
    vector<int> tmp;
    for(int i = 0; i < 36; i++){
        transitions[i].clear();
        for(int j = 0; j < n; j++){
            transitions[i].push_back(tmp);
        }
    }
}

void initAns(){
    ans = "";
    for(int i = 0; i < inp.size(); i++)
        ans += "N";
}

void getInput(){
    cin >> inp >> n >> a >> t;
    initVectors();
    for(int i = 0; i < a; i++){
        int acc;
        cin >> acc;
        accepts[acc] = true;
    }
    for(int i = 0; i < n; i++){
        int num;
        cin >> num;
        for(int j = 0; j < num; j++){
            char c; int ind;
            cin >> c >> ind;
            transitions[calculateCharIndex(c)][i].push_back(ind);
        }
    }
    initAns();
}

int main() {
    ios_base::sync_with_stdio(false);
    getInput();
    simulate();
    cout << ans << endl;
}