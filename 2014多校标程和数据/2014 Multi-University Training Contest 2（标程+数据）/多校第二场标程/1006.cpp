#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>
#define REP(i,n) for (int i=1;i<=(n);++i)
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,a,b) for (int i=(a);i>=(b);--i)
#define FEC(p,u) for (edge*p=head[u];p;p=p->nxt)
using namespace std;
typedef long long LL;

struct point{
	int x, y;
	point(){}
	point(int X, int Y):x(X), y(Y){}
};
bool operator<(point u, point v){ return u.x < v.x || u.x == v.x && u.y > v.y; }

int n;

struct hull{
	multiset<point> left, right;
	int top;
	LL s;
	void init(point u){
		left.clear(); left.insert(u);
		right.clear(); right.insert(u);
		top = u.y;
		s = 0;
	}
	void update(point x){
		set<point>::iterator v = left.insert(x), u = v, w = v, p;
		++w;
		if (v == left.begin()){
			while (w != left.end() && v->y >= w->y){
				p = w; ++p;
				if (p != left.end()) s -= 1LL*w->y*(p->x-w->x); 
				left.erase(w);
				w = v; ++w;
			}
			if (w != left.end()) s += 1LL*v->y*(w->x-v->x);
		}else{
			--u;
			if (u->y >= v->y) left.erase(v);
			else{
				if (w != left.end()){
					s -= 1LL*u->y*(w->x-u->x);
					while (w != left.end() && v->y >= w->y){
						p = w; ++p;
						if (p != left.end()) s -= 1LL*w->y*(p->x-w->x); 
						left.erase(w);
						w = v; ++w;
					}
					if (w != left.end()) s += 1LL*v->y*(w->x-v->x);
				}
				s += 1LL*u->y*(v->x-u->x);
			}
		}
		
		v = right.insert(x), u = v, w = v;
		++w;
		if (v == right.begin()){
			if (v->y < w->y) right.erase(v);
			else s += 1LL*w->y*(w->x-v->x);
		}else{
			--u;
			if (w == right.end() || v->y > w->y){
				if (w != right.end()){ s -= 1LL*w->y*(w->x-u->x); s += 1LL*w->y*(w->x-v->x); }
				while (v != right.begin() && v->y > u->y){
					p = u;
					if (p != right.begin()){ --p; s -= 1LL*u->y*(u->x-p->x); }
					right.erase(u);
					u = v; if (v != right.begin()) --u;
				}
				if (v != right.begin()) s += 1LL*v->y*(v->x-u->x);
			}else right.erase(v);
		}
	}
}upper, lower;
int main(){
	//freopen("in.txt", "r", stdin);
	//freopen("1.txt", "w", stdout);
	while (scanf("%d", &n) != EOF){
		int tx, ty;
		scanf("%d%d", &tx, &ty);
		upper.init(point(tx, ty));
		lower.init(point(tx, -ty));
		printf("0\n");
		FOR(i,2,n){
			scanf("%d%d", &tx, &ty);
			upper.update(point(tx, ty));
			lower.update(point(tx, -ty));
			printf("%I64d\n", upper.s+lower.s);
		}
	}
	return 0;
}

