// https://vjudge.net/contest/522920#problem/J

#include <bits/stdc++.h>
using namespace std;
int t, n;
char scores[20000];
string newCurr, answers[20000], score;
unordered_map<string, int> mp;
bool wrongString;
int halfScore, leftedScore, Case;
long long ans;
 
int calcScore(string &Rans, string &Sans){
    int sc = 0;
    int startInd = 0;
    if(Case == 2)
        startInd = 5;
    for(int i = 0; i < 5; i++){
        sc+= Sans[startInd+i] == Rans[i];
    }
    return sc;
}
 
void calcAns(string &curr){
    wrongString = false;
    score = "";
    for(int i = 0; i < n; i++){
        halfScore = calcScore(curr, answers[i]);
        leftedScore = scores[i] - '0' - halfScore;
        if(leftedScore < 0 || leftedScore > 5){
            wrongString = true;
            break;
        }
        score+= '0' + halfScore;
    }
    if(wrongString)
        return;
    ans += mp[score];
}
 
void buildMap(string &curr){
    wrongString = false;
    score = "";
    for(int i = 0; i < n; i++){
        leftedScore = scores[i] - '0' - calcScore(curr, answers[i]);
        if(leftedScore < 0 || leftedScore > 5){
            wrongString = true;
            break;
        }
        score += '0' + leftedScore;
    }
    if(wrongString)
        return;
    mp[score]++;
}
 
void generateStrings(string curr){
    if(curr.length() == 5){
        if(Case == 1)
            buildMap(curr);
        else
            calcAns(curr);
        return;
    }
    for(char a = 'A'; a <= 'D'; a++){
        newCurr = curr;
        newCurr += a;
        generateStrings(newCurr);
    }
}
 
int main(){
    cin >> t;
    for(int h = 0; h < t; h++){
        ans = 0;
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> answers[i];
            int sc;
            cin >> sc;
            sc /= 10;
            scores[i] = '0' + sc;
        }
        Case = 1;
        generateStrings("");
        Case = 2;
        generateStrings("");
        cout << ans << endl;
        mp.clear();
    }
}