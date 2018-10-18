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
#define mp make_pair

using namespace std;

const int MOD = 1000000007;
const int N = 1000010;
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

int tot, dfs_clock, bcc_cnt;
int to[M], nxt[M], head[N], dfn[N], low[N], iscut[N], bccno[N];
stack<pair<int, int> >stk;
vector<int>bcc[N];

void init() {
    tot = dfs_clock = bcc_cnt = 0; memset(head, 0, sizeof(head));
    memset(dfn, 0, sizeof(dfn)); memset(iscut, 0, sizeof(iscut));
    memset(bccno, 0, sizeof(bccno));
}

void addEdge(int u, int v) {
    to[++tot] = v, nxt[tot] = head[u], head[u] = tot;
}

void dfs(int u, int fa = -1) {
    dfn[u] = low[u] = ++dfs_clock;
    int child = 0;
    for(int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if(!dfn[v]) {
            stk.push(make_pair(u, v)), child++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {
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
                    if(a == u && b == v) break ;
                }
            }
        } else if(dfn[v] < dfn[u] && v != fa) {
            stk.push(make_pair(u, v));
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(fa < 0 && child == 1) iscut[u] = 0;
}

int main() {
    //freopen("in.txt", "r", stdin);
    int m, T = 0;
    while(scanf("%d", &m) && m) {
        init();
        int n = 0;
        for(int i = 1, u, v; i <= m; i++) {
            scanf("%d%d", &u, &v);
            n = max(n, max(u, v));
            addEdge(u, v); addEdge(v, u);
        }
        for(int i = 1; i <= n; i++) if(!dfn[i]) dfs(i);
        LL ans1 = 0, ans2 = 1;
        for(int i = 1; i <= bcc_cnt; i++) {
            int cnt = 0;
            for(int j = 0, lim = bcc[i].size(); j < lim; j++) if(iscut[bcc[i][j]]) cnt++;
            if(cnt == 1) {
                ans1++, ans2 *= (bcc[i].size()-1);
            }
        }
        if(bcc_cnt == 1) {
            ans1 = 2, ans2 = 1LL*bcc[1].size()*(bcc[1].size()-1)/2;
        }
        printf("Case %d: %lld %lld\n", ++T, ans1, ans2);
    }
}
