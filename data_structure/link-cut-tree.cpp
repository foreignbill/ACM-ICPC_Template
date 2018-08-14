#include <bits/stdc++.h>

using namespace std;

const int N=100005;
vector<int> e[N];
int anc[17][N];
struct node* null;
struct node {
    node *f, *ch[2];
    int s;
    void pushup() { s=1+ch[0]->s+ch[1]->s; }
    bool d() { return f->ch[1]==this; }
    void setc(node* c, bool d) { ch[d]=c; c->f=this; }
    bool check() { return  f==null || (f->ch[0]!=this && f->ch[1]!=this); } //check操作是lct特地的，因为为了省空间，我们不开n颗splay，只用节点关联就行了，这样就无法避免父亲没有这个孩子的情况。所以还要特判
}*nd[N];
 
void rot(node* r) {
    node* f=r->f; bool d=r->d();
    if(f->check()) r->f=f->f;
    else f->f->setc(r, f->d()); //这里一定要这样写，不然会让null的孩子改变，这样在splay的循环就会死循环T_T
    f->setc(r->ch[!d], d);
    r->setc(f, !d);
    f->pushup();
}
 
inline void splay(node* r) {
    while(!r->check())
        if(r->f->check()) rot(r);
        else r->d()==r->f->d()?(rot(r->f), rot(r)):(rot(r), rot(r));
    r->pushup();
}
 
inline void access(node* f) {
    for(node* c=null; f!=null; f=f->f) {
        splay(f);
        f->setc(c, 1);
        f->pushup();
        c=f;
    }
}
 
inline void link(node* c, node* f) {
    access(c); splay(c);
    c->ch[0]->f=null; c->ch[0]=null; c->f=f; c->pushup();
}
 
inline void init() {
    null=new node; null->s=0; null->f=null->ch[0]=null->ch[1]=null;
}

void dfs(int id,int fa) {
    anc[0][id] = fa;
    for(int i=1;i<17;i++)
        anc[i][id] = anc[i-1][anc[i-1][id]];
    for(auto ep : e[id]) {
        dfs(ep,id);
    }
}

int get_fa(int id,int x) {
    int now = 0;
    int fa = id;
    for(int i=16;i>=0;i--)
        if(now+(1<<i) <= x) {
            now += (1<<i);
            fa = anc[i][fa];
        }
    if(now == x) return fa;
    else return 0;
}
 
int main() {
	//freopen("input.txt","r",stdin);
    int T;for(scanf("%d",&T);T--;) {
        init();
        int n, t, q, opt, id;
        scanf("%d",&n);
        for(int i=1;i<=n;i++) {
            nd[i]=new node;
            nd[i]->s=1;
            nd[i]->ch[0]=nd[i]->ch[1]=nd[i]->f=null;
        }
        for(int i=1;i<=n;i++) e[i].clear();
        for(int i=2;i<=n;i++) {
            scanf("%d",&t);
            e[t].push_back(i);
        }
        memset(anc,0,sizeof anc);
        dfs(1,0);
        for(int i=1;i<=n;i++) {
            scanf("%d",&t);
            int fa = get_fa(i,t);
            if(fa) {
                nd[i]->f=nd[fa];
            }
        }
        scanf("%d",&q);
        while(q--) {
            scanf("%d",&opt);
            if(opt == 1) {
                scanf("%d",&t);
                access(nd[t]);
                splay(nd[t]);
                printf("%d\n",nd[t]->s);
            } else {
                scanf("%d%d",&id,&t);
                int fa = get_fa(id,t);
                if(fa) {
                    link(nd[id],nd[fa]);
                } else {
                    link(nd[id],null);
                }
            }
        }
    }
    return 0;
}