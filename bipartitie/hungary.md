## 匈牙利算法

~~~C++
bool hungary(int u) {
    vis[u] = clk;
    int v;
    for(int i = head[u]; i; i = nxt[i]) if(vis[v = to[i]] != clk) {
        vis[v] = clk;
        if(!xlink[v] || hungary(ylink[v])) {
            xlink[u] = v, ylink[v] = u;
            return true;
        }
    }
    return false;
}
~~~



## Hopcroft-Karp

```c++
int n, m, w;
int vis[N], xlink[N], ylink[N], dis[N];
vector<int>G[N];

bool BFS() {
    queue<int>q;
    memset(dis, -1, sizeof(dis));
    for(int i = 1; i <= m; i++)
        if(xlink[i] == -1) {
            q.push(i); dis[i] = 0;
        }
    w = INT_INF;
    while(!q.empty()) {
        int p = q.front(); q.pop();
        if(dis[p] > w) break;
        for(int i = 0; i < G[p].size(); i++) {
            int l = G[p][i];
            if(dis[l] == -1) {
                dis[l] = dis[p] + 1;
                if(ylink[l] == -1) w = dis[l];
                else {
                    dis[ylink[l]] = dis[l] + 1;
                    q.push(ylink[l]);
                }
            }
        }
    }
    return w != INT_INF;
}

int Find(int u) {
    for(int i = 0; i < G[u].size(); i++) {
        int l = G[u][i];
        if(!vis[l] && dis[l] == dis[u] + 1) {
            vis[l] = 1;
            if(ylink[l] != -1 && dis[l] == w) continue;
            if(ylink[l] == -1 || Find(ylink[l])) {
                xlink[u] = l, ylink[l] = u;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d%d", &n, &m);
    int u, v;
    while(scanf("%d%d", &u, &v) != EOF) G[u].push_back(v);
    memset(xlink, -1, sizeof(xlink));
    memset(ylink, -1, sizeof(ylink));
    int ans = 0;
    while(BFS()) {
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= m; i++)
            if(xlink[i] == -1) ans += Find(i);
    }
    printf("%d\n", ans);
}
```

