### 计算每个子树中节点数最多的层

```c++
#include <iostream>
#include <cstdio>
#include <vector>
#define mp make_pair

using namespace std;

const int MAXN = 1000010;
struct node{
    vector<int>*V;
    int mx;
    int sz() { return V->size(); }
    void add(int x, int y) {
        if(x < sz()) (*V)[x] += y;
        else V->push_back(y);
        if(mp((*V)[x], x) > mp((*V)[mx], mx)) mx = x;
    }
}f[MAXN];
int tot;
int to[MAXN<<1], _next[MAXN<<1], head[MAXN], ans[MAXN];

void addEdge(int u, int v) {
    to[++tot] = v, _next[tot] = head[u], head[u] = tot;
}

node merge(node a, node b) {
    if(a.sz() < b.sz()) swap(a, b);
    node c;
    c.V = a.V;
    c.mx = a.mx;
    int as = c.sz(), bs = b.sz();
    for(int i = 0; i < bs; i++) c.add(as-i-1, (*(b.V))[bs-i-1]);
    return c;
}

void dfs(int u, int fa = -1) {
    f[u].mx = 0;
    f[u].V = new vector<int>(0);
    for(int i = head[u]; i; i = _next[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u);
        f[u] = merge(f[u], f[v]);
    }
    f[u].add(f[u].sz(), 1);
    ans[u] = f[u].sz()-f[u].mx-1;
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1, x, y; i < n; i++) {
        scanf("%d%d", &x, &y);
        addEdge(x, y); addEdge(y, x);
    }
    dfs(1);
    for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
}
```

