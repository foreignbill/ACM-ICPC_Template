/*
$x\equiv c1(\mod m1)$

$x\equiv c2(\mod m2)$

可以合并，条件为$(m1,m2)|(c2-c1)$.

$m=\frac{m1*m2}{(m1,m2)}$.

$c=inv(\frac{m1}{(m1,m2)},\frac{m2}{(m1,m2)})\frac{c2-c1}{(m1,m2)}\mod \frac{m2}{(m1,m2)}m1+c1$,

合并成$x\equiv c(\mod m)$.

*/

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;

ll exgcd(ll a,ll b,ll&x,ll&y){
  if(!b)return x=1,y=0,a;
  ll d=exgcd(b,a%b,x,y),t=x;
  return x=y,y=t-a/b*y,d;
}

int n;
ll ans, a1, a2, a3, r1, r2, r3, x, y, tmp;

int main() {
    while (~scanf("%d", &n)) {
        scanf("%lld%lld", &a1, &r1);
        ans = (r1 % a1 + a1) % a1;
        while (--n) {
            scanf("%lld%lld", &a2, &r2);
            if (ans == -1) continue;
            tmp = exgcd(a1, a2, x, y);
            if ((r1 - r2) % tmp != 0) {
                ans = -1;
                continue;
            }
            x = x * (r2 - r1) / tmp;
            x = (x % a2 + a2) % a2;
            r1 = r1 + a1 * x;
            a1 = a1 * a2 / tmp;
            ans = (r1 % a1 + a1) % a1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}