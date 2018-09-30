/*
* @Author: foreignbill
* @Date:   2018-09-30 17:41:09
*/

/*
	hdu 3507
	f[i] = min(f[j] + (A[i] - A[j]) ^ 2) + M
	k < j < i
	2A[i] < (F[j] + A[j] ^ 2 - F[k] - A[k] ^ 2) / (A[j] - A[k])
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 500005;
int dp[500005];
int Q[1500005];
int sum[500005];
int f,r,n,m;

int getDP(int i,int j){
    return dp[j]+m+(sum[i]-sum[j])*(sum[i]-sum[j]);
}

int getup(int i,int j){
    return dp[i]+sum[i]*sum[i]-dp[j]-sum[j]*sum[j];
}

int getdown(int i,int j){
    return 2*(sum[i]-sum[j]);
}

int main(){
    //freopen("in.txt","r",stdin);
    while(~scanf("%d%d",&n,&m)){
        for(int i=1;i<=n;i++)
            scanf("%d",sum+i);
        dp[0]=0;
        for(int i=1;i<=n;i++)
            sum[i]+=sum[i-1];
        f=r=0;
        Q[r++]=0;
        for(int i=1;i<=n;i++){
            while(f+1<r && getup(Q[f+1],Q[f]) <= sum[i]*getdown(Q[f+1],Q[f]) )
                f++;
            dp[i]=getDP(i,Q[f]);
            while(f+1<r && getup(i,Q[r-1])*getdown(Q[r-1],Q[r-2]) <= getup(Q[r-1],Q[r-2])*getdown(i,Q[r-1]))
                r--;
            Q[r++]=i;
        }
        printf("%d\n",dp[n]);
    }
    return 0;
}