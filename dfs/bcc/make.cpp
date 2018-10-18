#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
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

int main() {
    freopen("in.txt", "w", stdout);
    srand(time(NULL));
    int T = 5;
    while(T--) {
        int n = 10, m = 30;
        printf("%d %d\n", n, m);
        for(int i = 1; i <= m; i++) {
            int a = rand()%n+1, b = rand()%n+1;
            printf("%d %d\n", a, b);
        }
    }
    printf("0 0\n");
}
