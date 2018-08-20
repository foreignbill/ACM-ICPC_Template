/*
* @Author: foreignbill
* @Date:   2018-08-20 10:52:27
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXL = 62;
struct liner_base {
	vector<ll> V;
	vector<ll> tmp;
	int n;
	void init(ll a[], int n) {
		this->n = n;
		for(int i=0;i<=MAXL;i++) tmp.push_back(0);
		for(int i=1;i<=n;i++) {
			for(int j=MAXL;j>=0;j--) {
				if(!(a[i]>>j)) continue;
				if(tmp[j]==0) {
					tmp[j]=a[i];
					break;
				}
				a[i] ^= tmp[j];
			}
		}
	}
	ll querymax() {
		ll ret = 0;
		for(int i=MAXL;i>=0;i--)
			if((ret ^ tmp[i]) > ret) ret = ret ^ tmp[i];
		return ret;
	}
}lb;

int n;
ll a[55];

int main () {
	cin >> n;
	for(int i=1;i<=n;i++)
		cin >> a[i];
	lb.init(a,n);
	cout << lb.querymax() << endl;
	return 0;
}