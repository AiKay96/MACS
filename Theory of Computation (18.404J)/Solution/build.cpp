#include<bits/stdc++.h>
using namespace std;

typedef struct{
    int n;
    vector<vector<int> > transitions[36];
    vector<bool> accepts;
}NFA;

char getChar(int a){
    if(a < 26)
        return 'a' + a;
    return '0' + a - 26;
}
bool isChar(char c){
    if(c == 'E')
        return true;
    if(c <= 'z' && c >= 'a')
        return true;
    if(c <= '9' && c >= '0')
        return true;
    return false;
}

int calculateCharIndex(char c){
    if(c >= 'a')
        return c - 'a';
    return 26 + c - '0';
}

void initNFA(NFA &a, int n){
    a.n = n;
    a.accepts = vector<bool> (n, false);
    vector<int> tmp;
    for(int i = 0; i < 36; i++)
        for(int j = 0; j < n; j++)
            a.transitions[i].push_back(tmp);
}

NFA getConcatNFA(NFA &a, NFA &b){
    NFA c;
    initNFA(c, a.n + b.n - 1);
    for(int i = 0; i < 36; i++)
        for(int j = 0; j < a.n; j++)
            for(int k = 0; k < a.transitions[i][j].size(); k++)
                c.transitions[i][j].push_back(a.transitions[i][j][k]);
    for(int i = 0; i < 36; i++)
        for(int k = 0; k < b.transitions[i][0].size(); k++)
            for(int j = 0; j < a.n; j++)
                if(a.accepts[j])
                    c.transitions[i][j].push_back(b.transitions[i][0][k] + a.n - 1);
    for(int i = 0; i < 36; i++)
        for(int j = 1; j < b.n; j++)
            for(int k = 0; k < b.transitions[i][j].size(); k++)
                c.transitions[i][a.n - 1 + j].push_back(b.transitions[i][j][k] + a.n - 1);
    if(b.accepts[0])
        for(int i = 0; i < a.accepts.size(); i++)
            c.accepts[i] = a.accepts[i];
    for(int i = 1; i < b.accepts.size(); i++)
        c.accepts[a.n - 1 + i] = b.accepts[i];
    return c;
}

NFA getUnionNFA(NFA &a, NFA &b){
    NFA c;
    initNFA(c, a.n + b.n - 1);
    for(int i = 0; i < 36; i++)
        for(int j = 0; j < a.n; j++)
            for(int k = 0; k < a.transitions[i][j].size(); k++)
                c.transitions[i][j].push_back(a.transitions[i][j][k]);
    for(int i = 0; i < 36; i++)
        for(int k = 0; k < b.transitions[i][0].size(); k++)
                c.transitions[i][0].push_back(b.transitions[i][0][k] + a.n - 1);
    for(int i = 0; i < 36; i++)
        for(int j = 1; j < b.n; j++)
            for(int k = 0; k < b.transitions[i][j].size(); k++)
                c.transitions[i][a.n - 1 + j].push_back(b.transitions[i][j][k] + a.n - 1);
    for(int i = 0; i < a.accepts.size(); i++)
        c.accepts[i] = a.accepts[i];
    if(b.accepts[0])
        c.accepts[0] = true;
    for(int i = 1; i < b.accepts.size(); i++)
        c.accepts[a.n  - 1 + i] = b.accepts[i];
    return c;
}

NFA getStarNFA(NFA& a){
    NFA b = a;
    for(int i = 0; i < 36; i++)
        for(int k = 0; k < a.transitions[i][0].size(); k++)
            for(int j = 0; j < a.n; j++)
                if(a.accepts[j])
                    b.transitions[i][j].push_back(a.transitions[i][0][k]);
    b.accepts[0] = true;
    return b;
}

NFA getCharNFA(char c){
    if(c == 'E'){
        NFA ans;
        initNFA(ans, 1);
        ans.accepts[0] = true;
        return ans;
    }
    NFA ans;
    initNFA(ans, 2);
    ans.transitions[calculateCharIndex(c)][0].push_back(1);
    ans.accepts[1] = true;
    return ans;
}

NFA getNFA(string postfix){
    stack<NFA> st;
    for(int i = 0; i < postfix.length(); i++){
        if(isChar(postfix[i])){
            NFA a = getCharNFA(postfix[i]);
            st.push(a);
        }
        if(postfix[i] == '.'){
            NFA a = st.top();
            st.pop();
            NFA b = st.top();
            st.pop();
            NFA c = getConcatNFA(b, a);
            st.push(c);
        }
        if(postfix[i] == '|'){
            NFA a = st.top();
            st.pop();
            NFA b = st.top();
            st.pop();
            NFA c = getUnionNFA(b, a);
            st.push(c);
        }
        if(postfix[i] == '*'){
            NFA a = st.top();
            st.pop();
            NFA b = getStarNFA(a);
            st.push(b);
        }
    }
    return st.top();
}

string getPostfix(string regex){
    string postfix = "";
    stack<char> st;
    for(int i = 0; i < regex.length(); i++){
        //case (
        if(regex[i] == '(' && regex[i+1] != ')')
            st.push('(');
        //case a
        if(isChar(regex[i])){
            postfix += regex[i];
        }
        //case .
        if(regex[i] == '.'){
            while(!st.empty() && (st.top() == '.' || st.top() == '*')){
                postfix += st.top();
                st.pop();
            }
            st.push('.');
        }
        //case |
        if(regex[i] == '|'){
            while(!st.empty() && (st.top() == '|' || st.top() == '*' || st.top() == '.')){
                postfix += st.top();
                st.pop();
            }
            st.push('|');
        }
        //case *
        if(regex[i] == '*'){
            while(!st.empty() && st.top() == '*'){
                postfix += st.top();
                st.pop();
            }
            st.push('*');
        }
        //case )
        if(regex[i] == ')'){
            while(st.top() != '('){
                postfix += st.top();
                st.pop();
            }
            st.pop();
        }
    }
    while(!st.empty()){
        postfix += st.top();
        st.pop();
    }
    return postfix;
}

string fixRegex(string regex){
    string eregex = "";
    for(int i = 0; i < regex.length(); i++){
        if(regex[i] == '(' && regex[i+1] == ')'){
            eregex += 'E';
            i++;
        }else{
            eregex += regex[i];
        }
    }
    string answer = "";
    for(int i  = 0; i < eregex.length() - 1; i++){
        answer += eregex[i];
        if((isChar(eregex[i]) && (isChar(eregex[i+1]) || eregex[i+1] == '(' )) || 
            (eregex[i] == '*' && (isChar(eregex[i+1]) || eregex[i+1] == '(' ))){
            answer += '.';
        }
        if(eregex[i] == ')' && (isChar(eregex[i+1]) || eregex[i+1] == '(' ))
            answer += '.';
    }
    answer += eregex[eregex.length() - 1];
    return answer;
}

void coutNFA(NFA& ans){
    int n = ans.n;
    int a = 0;
    int t = 0;
    for(int i = 0; i < n; i++)
        if(ans.accepts[i])
            a++;
    for(int i = 0; i < 36; i++)
        for(int j = 0; j < n; j++)
            t += ans.transitions[i][j].size();
    cout << n << " " << a << " " << t << endl;
    for(int i = 0; i < n; i++)
        if(ans.accepts[i])
            cout << i << " ";
    cout << endl;
    for(int j = 0; j < n; j++){
        int num = 0;
        for(int i = 0; i < 36; i++)
            num += ans.transitions[i][j].size();
        cout << num;
        for(int i = 0; i < 36; i++)
            for(int  k = 0; k < ans.transitions[i][j].size(); k++)
                cout << " " << getChar(i) << " " << ans.transitions[i][j][k];
        cout << endl;
    }
}

int main(){
  	ios_base::sync_with_stdio(false);
    string regex;
    cin >> regex;
    NFA ans = getNFA(getPostfix(fixRegex(regex)));
    coutNFA(ans);
}