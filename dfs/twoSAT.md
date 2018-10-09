## 2-SAT

### 字典序

逐一考虑每个没有赋值的变量，先假定为真，然后沿有向边标记所有能标记的节点，如果过程中发现某变量的两个对立节点都被标记，则不能为真。然后假定为假，再次进行标记，如果还是不能标记，则无解，不需要回溯。

~~~c++
/* poi2001 和平委员会
根据宪法，Byteland 民主共和国的公众和平委员会应该在国会中通过立法程序来创立。不幸的是，由于某些党派代表之间的不和睦而使得这件事存在障碍。

此委员会必须满足下列条件：
每个党派都在委员会中恰有1个代表，
如果2个代表彼此厌恶，则他们不能都属于委员会。

每个党在议会中有2个代表。代表从1编号到2n。 编号为2i−1和2i的代表属于第i个党派。
*/

int tot, c;
int to[M], nxt[M], head[N], mark[N], S[N];

void addEdge(int u, int v) {
    to[++tot] = v, nxt[tot] = head[u], head[u] = tot;
}

void init() {
    tot = 0; memset(mark, 0, sizeof(mark));
    memset(head, 0, sizeof(head));
}

bool dfs(int u) {
    if(mark[u^1]) return false;
    if(mark[u]) return true;
    mark[u] = true, S[c++] = u;
    for(int i = head[u]; i; i = nxt[i]) if(!dfs(to[i])) return false;
    return true;
}

void twoSAT(int n) {
    for(int i = 0; i < 2*n; i += 2) if(!mark[i] && !mark[i^1]) {
        c = 0;
        if(!dfs(i)) {
            while(c > 0) mark[S[--c]] = false;
            if(!dfs(i+1)) {
                printf("NIE\n"); return ;
            }
        }
    }
    for(int i = 0; i < 2*n; i++) if(mark[i]) printf("%d\n", i+1);
}

int main() {
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 1, a, b; i <= m; i++) {
            scanf("%d%d", &a, &b);
            a--, b--;
            addEdge(a, b^1); addEdge(b, a^1);
        }
        twoSAT(n);
    }
}
~~~

### 强连通分量

对于每个析取范式$a \bigvee b$ ，连两条边$(\neg a, b)$和$(\neg b, a)$，然后求强连通分量，进行缩点

如果存在两个对立的变量在一个强连通分量里面，则无解，否则必有解

缩点之后的DAG里面，对于两个对立变量$a$和$b$，若$a$的拓扑序在后边，则$a$为真

~~~C++
bool twoSAT(int n) {
    for(int i = 1; i <= 2*n; i++) if(!dfn[i]) tarjan(i);
    for(int i = 1; i <= n; i++) if(sccno[i] == sccno[i+n]) {
        printf("NO\n"); return ;
    };
    printf("YES\n");
    for(int i = 1; i <= n; i++) {
        if(sccno[i] < sccno[i+n]) printf("true\n");
        else printf("false\n");
    }
}
~~~

