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
int to[M], nxt[M], head[N], dfn[N], low[N], iscut[N], bccno[N], cnt[N];
stack<pair<int, int> >stk;
vector<int>bcc[N];
struct node{
    int id, block;
}f[N];

void init() {
    tot = dfs_clock = bcc_cnt = 0; memset(head, 0, sizeof(head));
    memset(dfn, 0, sizeof(dfn)); memset(iscut, 0, sizeof(iscut));
    memset(bccno, 0, sizeof(bccno)); memset(f, 0, sizeof(f));
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

int cmp(const node&a, const node&b) {
    if(a.block == b.block) return a.id < b.id;
    return a.block > b.block;
}

int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int n, m;
    while(scanf("%d%d", &n, &m) && (n || m)) {
        init();
        int u, v;
        while(scanf("%d%d", &u, &v) && (u!=-1 && v!=-1)) {
            u++, v++;
            addEdge(u, v); addEdge(v, u);
        }
        for(int i = 1; i <= n; i++) if(!dfn[i]) dfs(i);
        for(int i = 1; i <= n; i++) f[i].id = i;
        for(int i = 1; i <= bcc_cnt; i++) {
            for(int j = 0, lim = bcc[i].size(); j < lim; j++) f[bcc[i][j]].block++;
        }
        sort(f+1, f+n+1, cmp);
        for(int i = 1; i <= m; i++) printf("%d %d\n", f[i].id-1, f[i].block);
    }
}
