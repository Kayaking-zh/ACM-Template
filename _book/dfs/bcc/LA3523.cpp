#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <ctime>
#include <cmath>
#include <cstring>
#include <algorithm>
#define LL long long
#define ULL unsigned long long
#define lson rt<<1, l, mid
#define rson rt<<1|1, mid+1, r
#define lowbit(x) x&-x

using namespace std;

const int MOD = 1000000007;
const int N = 1010;
const int M = 100010;
const int INT_INF = 0x3f3f3f3f;
const LL LL_INF = 0x3f3f3f3f3f3f3f3f;
struct Point{
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
};
typedef Point Vector;

LL Abs(LL x) { if(x > 0) return x; return -x; }
LL Gcd(LL m, LL n) { LL r = m%n; while(r) { m = n; n = r; r = m%n; } return n; }
LL Pow(LL m, LL n) { LL ans = 1; while(n) { if(n&1) ans = ans*m%MOD; n >>= 1; m = m*m%MOD; } return ans; }

/**
                                       *************   *************
                                     *********************************
                                   *************************************
                                   *************************************
                                   *************************************
                                   *************************************
                                   *************************************
                                   *************************************
                                    ***********************************
                                     *********************************
                                       *****************************
                                        ***************************
                                          ***********************
                                             *****************
                                               *************
                                                   *****
                                                     *
**/

int n, m, dfs_clock, bcc_cnt;
int dfn[N], low[N], iscut[N], vis[N], color[N], bccno[N], g[N][N];
stack<pair<int, int> >stk;
vector<int>bcc[N];

void dfs(int u, int fa = -1) {
    dfn[u] = low[u] = ++dfs_clock;
    int child = 0;
    for(int i = 1; i <= n; i++) if(g[u][i]) {
        if(!dfn[i]) {
            stk.push(make_pair(u, i));
            dfs(i, u);
            low[u] = min(low[u], low[i]);
            if(low[i] >= dfn[u]) {
                iscut[u] = true; bcc_cnt++;
                bcc[bcc_cnt].clear();
                for(; ; ) {
                    int a = stk.top().first, b = stk.top().second; stk.pop();
                    if(bccno[a] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(a); bccno[a] = bcc_cnt;
                    }
                    if(bccno[b] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(b); bccno[b] = bcc_cnt;
                    }
                    if(a == u && b == i) break ;
                }
            }
        } else if(dfn[i] < dfn[u] && i != fa) {
            stk.push(make_pair(u, i));
            low[u] = min(low[u], dfn[i]);
        }
    }
    if(fa < 0 && child == 1) iscut[u] = 0;
}

void init() {
    dfs_clock = bcc_cnt = 0;
    for(int i = 1; i <= n; i++) for(int j = i+1; j <= n; j++) g[i][j] = g[j][i] = 1;
    memset(iscut, 0, sizeof(iscut)); memset(dfn, 0, sizeof(dfn));
    memset(vis, false, sizeof(vis)); memset(bccno, 0, sizeof(bccno));
}

bool bipartite(int u, int id) {
    for(int i = 1; i <= n; i++) if(g[u][i]) {
        if(bccno[i] != id) continue ;
        if(color[i] == -1) {
            color[i] = (color[u]^1);
            if(!bipartite(i, id)) return false;
        } else {
            if(color[u] == color[i]) return false;
        }
    }
    return true;
}

int main() {
    freopen("in.txt", "r", stdin);
    while(scanf("%d%d", &n, &m) && (n || m)) {
        init();
        for(int i = 1, k1, k2; i <= m; i++) {
            scanf("%d%d", &k1, &k2);
            g[k1][k2] = g[k2][k1] = 0;
        }
        for(int i = 1; i <= n; i++) if(!dfn[i]) dfs(i);
        for(int i = 1; i <= bcc_cnt; i++) {
            memset(color, -1, sizeof(color));
            for(int j = 0, lim = bcc[i].size(); j < lim; j++) bccno[bcc[i][j]] = i;
            int u = bcc[i][0]; color[u] = 1;
            if(!bipartite(u, i)) for(int j = 0, lim = bcc[i].size(); j < lim; j++) vis[bcc[i][j]] = 1;
        }
        int ans = n;
        for(int i = 1; i <= n; i++) ans -= vis[i];
        printf("%d\n", ans);
    }
}
