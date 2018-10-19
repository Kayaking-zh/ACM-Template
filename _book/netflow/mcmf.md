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

