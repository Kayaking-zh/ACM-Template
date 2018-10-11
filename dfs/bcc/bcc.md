## 双联通分量

### 割点

1. 树根是割点当且仅当它有两个及以上的孩子
2. 非根节点$$ u $$是割点当且仅当$$u$$存在一个子节点$$v$$，$$v$$以及其子节点都没有反向边连向$$u$$的子节点

~~~c++
int tot, dfs_clock, bcc_cnt;
int to[M], nxt[M], head[N], dfn[N], low[N], iscut[N], bccno[N];

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
			child++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) iscut[u] = true;
        } else if(dfn[v] < dfn[u] && v != fa)
            low[u] = min(low[u], dfn[v]);
    }
    if(fa < 0 && child == 1) iscut[u] = 0;
}
~~~



### 点双联通分量

不同双联通分量之间最多只有一个公共点，且一定是割点。计算点双联通分量的过程和计算割点类似，用一个栈来保存在当前BCC中的边。

~~~c++
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
~~~



