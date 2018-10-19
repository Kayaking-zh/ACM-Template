## 最大流

```c++
const int N = 4100, M = 200010;
int tot = 1, src, sink;
int to[M], _next[M], cap[M], head[N], pre[N], vis[N], cur[N], used[N];

void addEdge(int u, int v, int c) {
    to[++tot] = v, _next[tot] = head[u], cap[tot] = c, head[u] = tot;
}

void init() {
    tot = 1; memset(head, 0, sizeof(head));
}

bool BFS() {
    memset(vis, false, sizeof(vis));
    queue<int>q; q.push(src);
    vis[src] = true;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = _next[i]) {
            int v = to[i];
            if(!cap[i] || vis[v]) continue ;
            vis[v] = true, pre[v] = pre[u]+1;
            q.push(v);
        }
    }
    return vis[sink];
}

int DFS(int u, int c) {
    if(u==sink || c==0) return c;
    int flow = 0, f;
    for(int &i = cur[u]; i; i = _next[i]) {
        int v = to[i];
        if(pre[v]==pre[u]+1 && (f=DFS(v, min(c, cap[i])))>0) {
            flow += f, c -= f, cap[i] -= f, cap[i^1] += f;
        }
    }
    return flow;
}

int maxFlow() {
    int flow = 0;
    while(BFS()) {
        memcpy(cur, head, sizeof(cur));
        flow += DFS(src, INT_INF);
    }
    return flow;
}
```

## 有上下界网络流

### 无源汇有上下界可行流

如果存在可行流，那么每条边的流量都大于等于流量的下界，因此可以令每条边的初始流量为流量的下界，在此基础上建立残量网络。初始流不一定满足流量守恒，考虑在残量网络上求出另一个不守恒的附加流。

1. 对于原图中每条$(u, v, l, r)$的边，在新图中建立$(u, v, r-l)$的边
2. $ du[i] $表示初始流中节点$i$的流入流量与流出流量之差
3. 对于新图，建立超级源点$source$与汇点$sink$
4. 对于满足$du[i] > 0$的节点$i$，在新图中建立$(source, i, du[i])$的边
5. 对于满足$du[i] < 0$的节点$i$，在信徒中建立$(i, sink, -du[i])$的边

若新图可以满流，则存在一个可行流，否则不存在。

```c++
bool lowbound_flow(int n, vector<int>U, vector<int>V, vector<int>L, vector<int>R) {
    dinic::init();
    memset(du, 0, sizeof(du));
    int ln = U.size();
    for(int i = 0; i < ln; i++) {
        if(R[i] < L[i]) return 0;
        dinic::addEdge(U[i], V[i], R[i]-L[i], i+1);
        dinic::addEdge(V[i], U[i], 0, 0);
        du[U[i]] -= L[i], du[V[i]] += L[i];
    }
    dinic::src = n+1, dinic::sink = n+2;
    int sum = 0;
    for(int i = 0; i <= n; i++) {
        if(du[i] > 0) {
            dinic::addEdge(dinic::src, i, du[i], 0);
            dinic::addEdge(i, dinic::src, 0, 0);
            sum += du[i];
        } else if(du[i] < 0) {
            dinic::addEdge(i, dinic::sink, -du[i], 0);
            dinic::addEdge(dinic::sink, i, 0, 0);
        }
    }
    return dinic::maxFlow() == sum;
}
```

### 有源汇有上下界可行流

连接一条$(sink, src, inf)$的边，问题转化为无源汇有上下界可行流

### 有源汇有上下界最大流

先求一个有源汇有上下界可行流，然后再在原来的残量网络上面进行增广，最后的最大流即为可行流（原图中$sink$到$src$的流量）$+$ 残量网络最大流

```c++
int lowboundMaxflow(int s, int t, int n, vector<int>U, vector<int>V, vector<int>L, vector<int>R) {
    memset(du, 0, sizeof(du)); dinic::init();
    int m = U.size();
    dinic::src = n+1, dinic::sink = n+2;
    for(int i = 0; i < m; i++) {
        if(L[i] > R[i]) return -1;
        dinic::addEdge(U[i], V[i], R[i]-L[i]);
        dinic::addEdge(V[i], U[i], 0);
        du[U[i]] -= L[i], du[V[i]] += L[i];
    }
    int sum = 0;
    for(int i = 0; i <= n; i++) {
        if(du[i] > 0) {
            dinic::addEdge(dinic::src, i, du[i]);
            dinic::addEdge(i, dinic::src, 0);
            sum += du[i];
        } else if(du[i] < 0) {
            dinic::addEdge(i, dinic::sink, -du[i]);
            dinic::addEdge(dinic::sink, i, 0);
        }
    }
    dinic::addEdge(t, s, INF), dinic::addEdge(s, t, 0);
    if(dinic::maxFlow() < sum) return -1;
    else {
        int flow = dinic::cap[dinic::tot];
        dinic::cap[dinic::tot] = dinic::cap[dinic::tot-1] = 0;
        for(int i = dinic::head[dinic::src]; i; i = dinic::nxt[i])
            dinic::cap[i] = dinic::cap[i^1] = 0;
        for(int i = dinic::head[dinic::sink]; i; i = dinic::nxt[i])
            dinic::cap[i] = dinic::cap[i^1] = 0;
        dinic::src = s, dinic::sink = t;
        return flow + dinic::maxFlow();
    }
}
```

### 有源汇有上下界最小流

求完可行流之后在残量网络上进行从$t$到$s$的最大流，可行流减去$t$到$s$的最大流即为最小流

## 最小费用最大流

```c++
void addEdge(int u, int v, int w, int c) {
    to[++tot] = v, nxt[tot] = head[u], cap[tot] = w, cost[tot] = c, head[u] = tot;
}

bool spfaMin(int &c, int &f) {
    for(int i = src; i <= sink; i++) d[i] = INT_INF, inq[i]=0;
    queue<int>q; q.push(src);
    d[src] = 0, inq[src] = 1, pre[src] = 0, a[src] = INT_INF;
    while(!q.empty()) {
        int p = q.front(); q.pop();
        inq[p] = 0;
        for(int i = head[p]; i; i = nxt[i]) {
            int l = to[i];
            if(cap[i] && d[l] > d[p] + cost[i]) {
                d[l] = d[p] + cost[i]; pre[l] = i; a[l] = min(a[p], cap[i]);
                if(!inq[l]) q.push(l); inq[l] = 1;
            }
        }
    }
    if(d[sink] == INT_INF) return false;
    c += d[sink]*a[sink], f += a[sink];
    int u = sink;
    while(u != src) {
        cap[pre[u]] -= a[sink], cap[pre[u]^1] += a[sink];
        u = to[pre[u]^1];
    }
    return true;
}
```

## 最大费用最大流

```c++
int tot = 1, src, sink;
int to[M], nxt[M], cap[M], cost[M], head[N], d[N], a[N], inq[N], pre[N];

void addEdge(int u, int v, int w, int c) {
    to[++tot] = v, nxt[tot] = head[u], cap[tot] = w, cost[tot] = c, head[u] = tot;
}

bool spfaMax(int &c, int &f) {
    for(int i = src; i <= sink; i++) d[i] = -INT_INF, inq[i]=0;
    queue<int>q; q.push(src);
    d[src] = 0, inq[src] = 1, pre[src] = 0, a[src] = INT_INF;
    while(!q.empty()) {
        int p = q.front(); q.pop();
        inq[p] = 0;
        for(int i = head[p]; i; i = nxt[i]) {
            int l = to[i];
            if(cap[i] && d[l] < d[p] + cost[i]) {
                d[l] = d[p] + cost[i]; pre[l] = i; a[l] = min(a[p], cap[i]);
                if(!inq[l]) q.push(l); inq[l] = 1;
            }
        }
    }
    if(d[sink] == -INT_INF) return false;
    c += d[sink]*a[sink], f += a[sink];
    int u = sink;
    while(u != src) {
        cap[pre[u]] -= a[sink], cap[pre[u]^1] += a[sink];
        u = to[pre[u]^1];
    }
    return true;
}
```