/*
* @Author: foreignbill
* @Date:   2018-08-19 10:53:25
*/

#include <bits/stdc++.h>

using namespace std;

struct MST {
	static const int maxn = 2e5 + 5;
	static const int maxm = 5e5 + 5;
	int n, m;
	int f[maxn];
	int u[maxm],v[maxm],w[maxm],rk[maxm];
	void init(int n, int m) {
		this->n = n;
		this->m = m;
		for(int i=1;i<=n;i++)
			f[i] = i;
		for(int i=1;i<=m;i++)
			rk[i] = i;
	}
	inline int find(int x) {
		return x==f[x]?x:f[x]=find(f[x]);
	}
	long long solve() {
		sort(rk+1,rk+1+m,[&](const int &a,const int &b){
			return w[a] < w[b];
		});
		long long ret = 0;
		int take = 0;
		for(int i=1;i<=m;i++) {
			int h1=find(u[rk[i]]), h2=find(v[rk[i]]);
			if(h1 == h2) continue;
			f[h1] = h2;
			ret += w[rk[i]];
			take++;
			if(take == n-1) break;
		}
		return ret;
	}
}G;

int n, m;

int main () {
	scanf("%d%d",&n,&m);
	G.init(n,m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&G.u[i],&G.v[i],&G.w[i]);
	cout << G.solve() << '\n';
	return 0;
}