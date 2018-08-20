#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double eps = 1e-12;

int dcmp(double x) {
	if(x > eps) return 1;
	if(x < -eps) return -1;
	return 0;
}

struct point {
	double x,y;
	point(){}
	point(double _x,double _y):x(_x),y(_y) {}
	void read() {
		scanf("%lf%lf",&x,&y);
	}
	friend point operator + (const point &a,const point &b) {
		return point(a.x+b.x,a.y+b.y);
	}
	friend point operator - (const point &a,const point &b) {
		return point(a.x-b.x,a.y-b.y);
	}
	friend bool operator == (const point &a,const point &b) {
		return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
	}
};

double det(const point &a,const point &b) {
	return a.x * b.y - a.y * b.x;
}

double dot(const point &a,const point &b) {
	return a.x * b.x + a.y * b.y;
}

struct polygon_convex {
	vector<point> P;
	polygon_convex(int size=0) {
		P.resize(size);
	}
};

bool comp_less(const point &a,const point &b) {
	if(a.x == b.x)
		return a.y < b.y;
	return a.x < b.x;
}

polygon_convex convex_hull(vector<point> a) {
	polygon_convex res(2*a.size()+5);
	sort(a.begin(),a.end(),comp_less);
	a.erase(unique(a.begin(),a.end()),a.end());
	int m=0;
	for(int i=0;i<a.size();i++) {
		while(m>1 && dcmp(det(res.P[m-1]-res.P[m-2],a[i]-res.P[m-2])) <= 0) m--;
		res.P[m++] = a[i];
	}
	int k=m;
	for(int i=(int)a.size()-2;i>=0;i--) {
		while(m>k && dcmp(det(res.P[m-1]-res.P[m-2],a[i]-res.P[m-2])) <= 0) m--;
		res.P[m++] = a[i];
	}
	res.P.resize(m);
	if(a.size() > 1) res.P.resize(m-1);
	return res;
}