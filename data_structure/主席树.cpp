#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 7;
int arr[N];  //arr[]  原数组的数在rank[] 中的位置;
int Rank[N]; //rank[] 原数组离散化
struct ChairTree{
    #define lson tree[rt].lc, tree[rt1].lc, l, m
    #define rson tree[rt].rc, tree[rt1].rc, m+1, r
    struct node{
        int lc, rc, w;
        node(){}
    } tree[N * 20];
    int root[N], cnt;
    void build(){
        root[0] = cnt = 0;
        memset(tree, 0, sizeof(tree));
    }
    void add(int pos, int val, int &rt, int rt1, int l, int r){
        tree[rt = ++cnt] = tree[rt1];
        tree[rt].w += val;
        if (l == r) return;
        int m = (l + r) >> 1;
        if (pos <= m) add(pos, val, lson);
        else add(pos, val, rson);
    }
    int query(int k, int rt, int rt1, int l, int r){
        if (l == r) return l;
        int lsize = tree[tree[rt1].lc].w - tree[tree[rt].lc].w;
        int m = (l + r) >> 1;
        if (lsize >= k) return query(k, lson);
        else return query(k - lsize, rson);
    }
} T;

int main(){
    //freopen("in.txt","r",stdin);
    int _, l, r, k, n, q;
    for (; ~scanf("%d%d", &n, &q);){
        T.build();
        for (int i = 1; i <= n; i++) {
            scanf("%d", &arr[i]);
            Rank[i] = arr[i];
        }
        sort(Rank + 1, Rank + n+1);//Rank 存储原值g
        int m = unique(Rank + 1, Rank + n +1) - (Rank + 1);
        for (int i = 1; i <= n; i++) {//离散化后的数组，仅仅用来更新
            arr[i] = lower_bound(Rank + 1, Rank + n+1, arr[i]) - Rank;
        }
        for (int i = 1; i <= n; i++){
            T.add(arr[i], 1, T.root[i], T.root[i-1], 1, n);
        }
        for (; q--;){
            scanf("%d%d%d", &l, &r, &k);
            int pos = T.query(k, T.root[l-1], T.root[r], 1, n);
            printf("%d\n", Rank[pos]);
        }
    }
    return 0;
}
/*
	K-th min.
*/