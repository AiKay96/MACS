// https://codeforces.com/contest/653/problem/D
// https://codeforces.com/problemset/problem/653/D

#include<bits/stdc++.h>
#define int long long
const int INF = 1000000000;
using namespace std;
 
struct edge{
    // წიბოს მეორე წვერო (u -> v u-ს შენახვა ძირითადად არ გვჭირდება)
    int v;
    // მაქსიმალური ნაკადი
    int maxFlow;
    // ამ მომენტში გამავალი ნაკადი.
    int flow;
    // ნარჩენი ნაკადი (კიდევ რამდენის გატარება შეიძლება)
    int res;
    // შეტრიალებული წიბოს მეორე ინდექსი (პირველი v-ს ტოლია)
    int inv;
 
    edge(int v, int maxFlow, int flow, int res, int inv) {
        this->v = v;
        this->maxFlow = maxFlow;
        this->flow = flow;
        this->res = res;
        this->inv = inv;
    }
};
vector<edge> tmp[51];
vector<edge> v[51];
int fx[51];
 
bool dfs(int current, int dest, int &minEdge) {
    // dest არის საბოლოო წვერო და თუ ვიპოვეთ, ესე იგი გზაც ნაპოვნია.
    if (current == dest) {
        return true;
    }
    fx[current] = 1;
    int j = 0;
    for (auto iter : v[current]) {
        j ++;
        // ნარჩენი ნაკადი მინიმუმ ერთი უნდა იყოს, რომ ამ წიბოში ნაკადის გატარება შეიძლებოდეს.
        if (!fx[iter.v] && iter.res > 0) {
            bool val = dfs(iter.v, dest, minEdge);
            if (val) {
                minEdge = min(minEdge, iter.res);
                // ყველა წვეროში ჩავწეროთ ნაპოვნი გზის შემდეგი წვეროს ინდექსს + 1 (0 რომ არ იყოს არც ერთი).
                fx[current] = j;
                return true;
            }
        }
    }
    return false;
}
 
void update(int current, int dest, int flow) {
    while (current != dest) {
        int i = fx[current] - 1;
        v[current][i].flow += flow;
        v[current][i].res -= flow;
 
        // შეტრიალებულ წიბოში ინფორმაციის განახლება.
        int revI = v[current][i].v;
        int revJ = v[current][i].inv;
        v[revI][revJ].flow -= flow;
        v[revI][revJ].res += flow;
        current = v[current][i].v;
    }
}
 
int flow(int s, int t) {
    int minEdge, flow = 0;
    do {
        minEdge = INT_MAX;
        memset(fx, 0, sizeof fx);
        if (dfs(s, t, minEdge)) {
            flow += minEdge;
            update(s, t, minEdge);
        }
    // თუ ერთი მაინც არ დაემატა ნაკადს და უსასრულობა დარჩა, ესე იგი მაქსიმუმია გატარებული და უნდა მოვრჩეთ.
    } while (minEdge != INT_MAX);
    return flow;
}
main() {
    int maxn = 51;
    int n, m, x;
    cin >> n >> m >> x;
    for (int i = 0; i < m; i ++) {
        int u, w, mx;
        cin >> u >> w >> mx;
        tmp[u].push_back(edge(w, mx, 0, mx, tmp[w].size()));
        tmp[w].push_back(edge(u, 0, 0, 0, tmp[u].size() - 1));
    }
    double l = 0; double r = 1000000000;
    for(int i = 0; i < 100; i++){
        double mid = (l + r) / 2;
        for(int j = 0; j < maxn; j++){
            v[j] = tmp[j];
            for(int k = 0; k < v[j].size(); k++){
                v[j][k].maxFlow = v[j][k].maxFlow / mid;
                v[j][k].res = v[j][k].res / mid;
            }
        }
        if(flow(1, n) >= x)
            l = mid;
        else
            r = mid;
    }
    double ans = (double)x*l;
    cout << setprecision(15) << ans << endl;
}