## 最佳完美匹配

~~~C++
bool match(int u) {
    S[u] = true;
    for(int v = 1; v <= n; v++) if(!T[v]) {
        int gap = lx[u]+ly[v]-w[u][v];
        if(gap == 0) {
            T[v] = true;
            if(!ylink[v] || match(ylink[v])) {
                xlink[u] = v, ylink[v] = u;
                return true;
            }
        } else {
            slack[v] = min(slack[v], gap);
        }
    }
    return false;
}

void update() {
    int a = inf;
    for(int i = 1; i <= n; i++) if(!T[i]) a = min(a, slack[i]);
    for(int i = 1; i <= n; i++) {
        if(S[i]) lx[i] -= a;
        if(T[i]) ly[i] += a;
        else slack[i] -= a;
    }
}

void KM() {
    for(int i = 1; i <= n; i++) {
        xlink[i] = ylink[i] = lx[i] = ly[i] = 0;
        for(int j = 1; j <= n; j++) lx[i] = max(lx[i], w[i][j]);
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) slack[j] = inf;
        while(true) {
            for(int j = 1; j <= n; j++) S[j] = T[j] = 0;
            if(match(i)) break; else update();
        }
    }
}
~~~

