## 生成树计数

Kirchhoff矩阵：对于无向图G，它的Kirchhoff矩阵为G对应的度数矩阵减去它的邻接矩阵

Matrix-Tree定理：对于无向图G，它的生成树个数等于其Kirchhoff矩阵任何一个$$n-1$$阶主子式的行列式的绝对值

~~~C++
LL det(LL A[N][N], int n) {
    int t = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = i+1; j <= n; j++) while(A[j][i]) {
            LL x = A[i][i]/A[j][i];
            t++;
            for(int k = 1; k <= n; k++)
                A[i][k] = (A[i][k]-x*A[j][k]%MOD+MOD)%MOD;
            for(int k = 1; k <= n; k++)
                swap(A[i][k], A[j][k]);
        }
    }
    LL ans = 1;
    for(int i = 1; i <= n; i++) ans = (ans*A[i][i])%MOD;
    if(t&1) ans = -ans;
    return (ans%MOD+MOD)%MOD;
}
~~~

