/*************************************************************************
	> File Name: test.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月23日 星期二 19时38分57秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX_N 1000
#define MAX_K 20
// N最大节点数，K代表最多向上跳2^MAX_K步
// 2^k方要大于总节点数,即向上能跳的层数
struct Edge {
    int v, n;       //g[i].v代表第i条边的目的顶点，g[i].n代表v的父亲节点先于第i条边插入的最后一条边
} g[MAX_N << 1];
int head[MAX_N + 5] = {0}, cnt = 0;     // head[i]代表从节点i出去的最后一条边的序号

inline void add(int a, int b) {
    g[++cnt].v = b;
    g[cnt].n = head[a];     // g.n表示什么??
    head[a] =  cnt;         // head[a]代表从a出发边的数目
    return ;
}

//gas[i][j] -> i节点往上跳2^j次方步所能达到的祖先节点编号
int gas[MAX_N][MAX_K] = {0}, dep[MAX_N] = {0};

void dfs(int u, int father) {
    gas[u][0] = father;
    dep[u] = dep[father] + 1;
    for (int i = 1; i < MAX_K; i++) {
        // 相当于向上跳i步
        gas[u][i] = gas[gas[u][i - 1]][i - 1];
    }
    // 分别遍历相连的点 ??
    for (int i = head[u]; i; i = g[i].n) {
        // 因为这个树我们将每一条边虚拟成了来回两条边
        // 所以可能形成环，当自环的时候跳过
        if (g[i].v == father) continue;
        dfs(g[i].v, u);
    }
    return ;
}
//0节点不用,
int lca(int a, int b) {
    // 交换a,b两节点的值 保证b是较深的
    // a^b = c则可用任意两个值去还原第三个值
    // 全为0 或者一定有两个1一个0
    if (dep[b] < dep[a]) {
        a ^= b;
        b ^= a;
        a ^= b;
    }
    int l = dep[b] - dep[a];
    // 对齐
    for (int i = 0; i < MAX_K; i++) {
        // 判断l的二进制为1的位
        // 这种做法称为倍增
        if ((l & (1 << i))) b = gas[b][i];
    }                   // 执行完for语句后，a和b位于同一深度
    if (a == b) return a;
    // 一起往上走
    // 二进制的每一位组合在一起可以遍历任意层次深度
    for (int i = MAX_K - 1; i >= 0; i--) {
        // 若lca上面相距5,则最多可以向上跳4,当相等时不跳,因为找到的不是最近的
        if (gas[a][i] != gas[b][i]) a = gas[a][i], b = gas[b][i];
    }       // 执行完for语句后，a和b位于于其最近公共节点的下一层
    return gas[a][0];
}
int main() {
    int n;                              // n代表节点数
    scanf("%d", &n);
    int a, b;
    for (int i = 1; i < n; i++) {       // 边数比节点数少1
        scanf("%d%d", &a, &b);
        add(a, b);                      // a, b代表边的两节点
        add(b, a);                      // 执行两次add是因为把每条边虚拟成来回的两条边
    }
    // 选哪个点当根节点和两点间的最短路径无关
    // 选1为根,父节点不存在,则设为0
    dfs(1, 0);                          // 不用0节点，假设1号节点的父亲为0节点
    while (scanf("%d%d", &a, &b) != EOF) {
        printf("lca(%d, %d) = %d, a->b = %d\n", a, b, lca(a, b), dep[a] + dep[b] - 2 * dep[lca(a, b)]);
    }
    return 0;
}
