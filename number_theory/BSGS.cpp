/*
求$a^x\equiv b(\mod p)$的$x$解。
$m=\left \lceil \sqrt{p} \right \rceil$.
令$x=im-j$，化为$(a^m)^i\equiv ba^j(\mod p)$.
$i=0,1,...,m$，求出$ba^i$，并记录对应$i$最大值。
$i=1,2,...,m$，寻找对应$(a^m)^i\equiv before$，break输出答案。
*/

#include <cstdio>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

typedef long long ll;

ll a,b,p;//a^x=b(mod p)
bool flag;

int len;
struct node{
    ll t,i;
}_hash[1<<16];

inline ll gcd(ll a,ll b){
    return b==0?a:gcd(b,a%b);
}

inline ll power(ll a,ll n,ll p){
    ll ret=1;ll now=a;
    while(n!=0){
        if(n&1)
            ret=ret*now%p;
        now=now*now%p;
        n>>=1;
    }
    return ret;
}

bool comp(node A,node B){
    if(A.t==B.t)
        return A.i<B.i;
    return A.t<B.t;
}

int Find(ll ret,int len){
    int l=1,r=len;
    int k=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(_hash[mid].t<ret)
            l=mid+1;
        else if(_hash[mid].t>ret)
            r=mid-1;
        else if(_hash[mid].t==ret)
            l=mid+1,k=_hash[mid].i;
    }
    return k;
}

inline void BSGS(ll a,ll b,ll p){
    if(/*gcd(a,p)!=1*/a % p == 0){//互质
        flag=0;
        return;
    }
    len=0;
    ll l=1,r=p;
    ll m;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(mid*mid>=p)
            r=mid-1,m=mid;
        else l=mid+1;
    }
    ll tmp=b%p;
    for(int i=0;i<=m;i++){
        len++;
        _hash[len].t=tmp;
        _hash[len].i=i;
        tmp=tmp*a%p;
    }
    sort(_hash+1,_hash+1+len,comp);
    tmp=power(a,m,p);
    ll ret=1;
    for(int i=1;i<=m;i++){
        ret=ret*tmp%p;
        int id=Find(ret,len);
        if(id!=-1){
            printf("%lld\n",m*i-id);
            flag=1;
            return;
        }
    }
}

int main(){
    while(~scanf("%lld%lld%lld",&p,&a,&b)){
        flag=0;
        BSGS(a,b,p);
        if(!flag)
            puts("no solution");
    }
    return 0;
}