
#include<iostream>
#include<algorithm>
#include<cassert>
#include<string>
#include<sstream>
#include<set>
#include<bitset>
#include<vector>
#include<stack>
#include<map>
#include<queue>
#include<deque>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cctype>
#include<list>
#include<complex>
#include<functional>
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;

#define me(s)  memset(s,0,sizeof(s))
#define rep(i,n) for(int i=0;i<(n);i++)
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair <int,int> P;


const int N=1000+10;
vector<int>g[N],bcc[N];
int color[N];
int odd[N];
int A[N][N];
int pre[N],bccno[N],iscut[N];
struct Edge{int u,v;};
stack<Edge>s;
int dfs_clock,bcc_cnt;

bool bipartite(int u,int b)
{
    int len=g[u].size();
    for(int i=0;i<len;i++)
    {
        int v=g[u][i];
        if(bccno[v]!=b)continue;
        if(color[v]==color[u])return false;
        if(!color[v])
        {
            color[v]=3-color[u];
            if(!bipartite(v,b))return false;
        }
    }
    return true;
}

int dfs(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    int child=0;
    for(int i=0;i<g[u].size();i++)
    {
        int v=g[u][i];
        Edge e=Edge{u,v};
        if(!pre[v])
        {
            s.push(e);
            child++;
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);
            if(lowv>=pre[u])
            {
                iscut[u]=1;
                bcc[++bcc_cnt].clear();
                for(;;)
                {
                    Edge x=s.top();s.pop();
                    if(bccno[x.u]!=bcc_cnt){bcc[bcc_cnt].push_back(x.u);bccno[x.u]=bcc_cnt;}
                    if(bccno[x.v]!=bcc_cnt){bcc[bcc_cnt].push_back(x.v);bccno[x.v]=bcc_cnt;}
                    if(x.u==u&&x.v==v)break;
                }
            }
        }
        else if(pre[v]<pre[u]&&v!=fa)
        {
            s.push(e);
            lowu=min(lowu,pre[v]);
        }
    }
    if(fa<0&&child>1)iscut[u]=1;
    return lowu;
}

void find_bcc(int n)
{
    dfs_clock=bcc_cnt=0;
    memset(pre,0,sizeof(pre));
    memset(iscut,0,sizeof(iscut));
    memset(bccno,0,sizeof(bccno));
    for(int i=0;i<n;i++)
        if(!pre[i])dfs(i,-1);
}


int main()
{
    freopen("in.txt", "r", stdin);
    int rnd=0;
    int n,m;
    while(~scanf("%d%d",&n,&m)&&n)
    {
        for(int i=0;i<n;i++)g[i].clear();
        me(A);
        for(int i=0;i<m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            u--,v--;
            A[u][v]=A[v][u]=1;
        }
        for(int u=0;u<n;u++)
            for(int v=u+1;v<n;v++)//将不相互憎恨的骑士之间加边
        if(!A[u][v]){g[u].push_back(v);g[v].push_back(u);}
        find_bcc(n);
        printf("%d\n", bcc_cnt);
        memset(odd,0,sizeof(odd));
        for(int i=1;i<=bcc_cnt;i++)
        {
            me(color);
            for(int j=0;j<bcc[i].size();j++)//先给同一个BCC的结点都加上相同的编号
                bccno[bcc[i][j]]=i, printf("%d ", bcc[i][j]+1);
            printf("\n");
            int u=bcc[i][0];
            color[u]=1;
            if(!bipartite(u,i))//如果该BCC不是二分图，那么对它上面的所有结点做标记
                for(int j=0;j<bcc[i].size();j++)
                odd[bcc[i][j]]=1;
        }
        int ans=n;
        for(int i=0;i<n;i++)
            if(odd[i])ans--;
        printf("%d\n",ans);
    }

}
