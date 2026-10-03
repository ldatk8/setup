/**
 *    author : Lăng Trọng Đạt
 *    created: 12-08-2025
**/
#include <bits/stdc++.h>
using namespace std;
#ifndef LANG_DAT
#define db(...) ;
#endif // LANG_DAT
#define int long long
#define f first
#define se second
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define FOR(i, a, b) for (int i = (a); (i) <= (b); (i++))
#define FD(i, a, b) for (int i = (b); (i) >= (a); (i--))
#define si(x) (int)(x.size())
bool mx(int& a, int b) { if (b > a) {a = b; return true;} return false;}
bool mi(int& a, int b) { if (b < a) {a = b; return true;} return false;}
using pii = pair<int, int>;
using vi = vector<int>;

const int INF = 1e18 + 5;
const int MOD = 1e9 + 7;

const int N = 1e5 + 5;
int g[N];
vector<int> adj[N];
int num_test, n, m, k, q, a, b, c;

namespace trau
{
    const int N = 5e3 + 5;
    int dp[N][N], d[N];
    void dfs(int v, int prv) {
        for (int u : adj[v]) {
            if (u == prv) continue;
            d[u] = d[v] + 1;
            dfs(u, v);
        }
        FOR(i, 0, n) dp[v][i] = 0;
        dp[v][d[v]] = g[0];
        FOR(dist, d[v] + 1, n - 1) {
            for (int u : adj[v]) {
                if (u != prv) {
                    dp[v][dist] += dp[u][dist];
                }
            }
            mi(dp[v][dist], g[dist - d[v]]);
        }
    }
    int solve() {
        dfs(1, 0);

        int ans = 0;
        FOR(i, 0, n - 1) {
            ans += dp[1][i];
        }

        return ans;
    }
} // namespace trau

namespace virtual_tree
{
    int in[N], out[N], d[N], timer = 0, rmq[20][2*N], D;
    int rmq2[20][N];
    vector<int> same_d[N];
    void euler(int v, int prv) {
        same_d[d[v]].push_back(v);
        in[v] = ++timer;
        rmq[0][timer] = v;
        for (int u : adj[v]) {
            if (u == prv) continue;
            d[u] = d[v] + 1;
            euler(u, v);
            rmq[0][++timer] = v;
        }
        out[v] = timer;
    }
    int min_d(int a, int b) {
        return (d[a] < d[b] ? a : b);
    }
    void build() {
        FOR(i, 0, n - 1) rmq2[0][i] = g[i];
        FOR(log, 0, 18) 
            FOR(i, 0, n - 1 - (1 << log)) 
                rmq2[log + 1][i] = min(rmq2[log][i], rmq2[log][i + (1 << log)]);
        FOR(log, 0, 18) 
            FOR(v, 1, timer - (1 << log))   
                rmq[log + 1][v] = min(rmq[log][v], rmq[log][v + (1 << log)]);

    }
    int lca(int a, int b) {
        int l = min(in[a],in[b]); int r = max(in[a], in[b]);
        int lg = 31 - __builtin_clz(r - l + 1);
        return min_d(rmq[lg][l], rmq[lg][r - (1 << lg) + 1]);
    }
 
    int min_range(int l, int r) {
        int lg = 31 - __builtin_clz(r - l + 1);
        return min(rmq2[lg][l], rmq2[lg][r - (1 << lg) + 1]);
    }

    vector<int> nxt[N];
    vector<int> build_vtree(vector<int>& node) {
        if (node.empty()) return {};
        sort(all(node), [&](int a, int b) -> bool { // sort by dfs order
            return in[a] < in[b];
        });
        vector<int> ans = node;
        FOR(i, 0, si(node) - 2) {
            ans.push_back(lca(node[i], node[i + 1]));
        }
        ans.push_back(1);
        sort(all(ans), [&](int a, int b) -> bool { // sort by dfs order
            return in[a] < in[b];
        });
        ans.resize(unique(all(ans)) - ans.begin()); 
        // hmm, in this case, i think last node will cover all be farther of all vertices in node

        // then we rebuild virtual tree 
        stack<int> s;
        for (int v : ans) { // because ans is in dfs order, so we will pop from s until s.back() is far of v
            nxt[v].clear();
            while (!s.empty() && !(in[s.top()] <= in[v] && out[v] <= out[s.top()])) s.pop();
            if (!s.empty()) nxt[s.top()].push_back(v);
            s.push(v);
        }

        return ans;
    }

    int dp(int v) {
        int cur = 0;
        for (int u : nxt[v]) {
            assert(d[u] > d[v]);
            cur += dp(u);
        }
        if (d[v] == D) cur = g[0];
        return min(cur, min_range(D - d[v], D));
    }
    int solve() {
        timer = 0;
        euler(1, -1);
        build();    

        int ans = 0;
        vector<int> use;
        for (D = 0; D < n; D++) {
            if (si(same_d[D]) == 0) break;
            vector<int> vtree = build_vtree(same_d[D]);
            ans += dp(vtree[0]);
            same_d[D].clear();
        }

        return ans;
    }
} // namespace virtual_tree

bool LangDatPBC(bool solve) {
    cin >> n;
    FOR(i, 0, n - 1) {
        cin >> g[i];
        adj[i + 1].clear();
    }
    FOR(i, 1, n - 1) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // cout << trau::solve();
    cout << virtual_tree::solve();

    return true;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    if (fopen("hi.inp", "r")) {
        freopen("hi.inp", "r", stdin);
    //    freopen("hi.out", "w", stderr);
    } 

    num_test = 1;
    cin >> num_test;
    FOR(test, 1, num_test) {
        cout << (LangDatPBC(test == 2) ? "\n" : "-1\n");
    }

}