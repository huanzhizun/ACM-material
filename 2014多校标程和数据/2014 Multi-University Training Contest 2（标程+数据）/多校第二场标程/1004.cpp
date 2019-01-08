#include <cstdio>
#define stype(x) (x->f->son[1] == x)
#define isroot(x) (!x->f || (x->f->son[0]!=x && x->f->son[1]!=x))
using namespace std;

template<typename T> void R(T &x) {
	char ch = getchar(); x = 0;
	for (; ch<'0'; ch=getchar());
	for (; ch>='0'; ch=getchar()) x = x*10+ch-'0';
}
const int N = 100005;
int n, m;
namespace LCT {
	const int N = 300005;
	struct node {
		node *f, *son[2];
		int key, s0, s1;
		inline void upd() {
			s0 = !key, s1 = key;
			if (son[0]) s0 += son[0]->s0, s1 += son[0]->s1;
			if (son[1]) s0 += son[1]->s0, s1 += son[1]->s1;
		}
	} ns[N];
	node* getroot(node *x) {
		for (; !isroot(x); x=x->f);
		return x;
	}
	inline void rot(node *x) {
		node *fa = x->f; int st = stype(x);
		if (!isroot(fa)) fa->f->son[stype(fa)]=x; x->f=fa->f;
		if (x->son[!st]) x->son[!st]->f=fa; fa->son[st]=x->son[!st];
		fa->f=x, x->son[!st]=fa;
		fa->upd();
	}
	void splay(node *x) {
		node *y = getroot(x)->f;
		while (x->f != y) {
			if (x->f->f!=y) {
				if (stype(x) == stype(x->f))
					rot(x->f); else
					rot(x);
			}
			rot(x);
		}
		x->upd();
	}
	void access(node *x) {
		splay(x); x->son[1] = NULL; x->upd();
		while (x->f) {
			splay(x->f);
			x->f->son[1] = x;
			x = x->f;
			x->upd();
		}
	}
	inline void link(node *x, node *y) { // link y to x
		splay(y); y->f = x;
	}
	inline void cut(node *x) {
		access(x); splay(x);
		if (!x->son[0]) return;
		x->son[0]->f = 0, x->son[0] = 0;
		x->upd();
	}
	inline node *kth(node *x, int k) {
		int ls; splay(x);
		while (1) {
			ls = x->son[0] ? x->son[0]->s0+x->son[0]->s1 : 0;
			if (ls > k) x = x->son[0]; else
			if (ls < k) x = x->son[1], k-=ls+1; else
				return splay(x), x;
		}
	}
	inline int rank(node *x) {
		splay(x);
		return x->son[0] ? x->son[0]->s0+x->son[0]->s1 : 0;
	} 
	inline void M(int x, int p, int c, int y, int q) {
		int s; node *sn;
		sn = ns+n+x; access(sn+n); s = rank(sn);
		node *l1=kth(sn, s+p-1), *c1=kth(l1, s+p), *l3=kth(c1, s+p+c-1), *c2=kth(l3, s+p+c);
		sn = ns+n+y; access(sn+n); s = rank(sn);
		node *l2=kth(sn, s+q), *c3=kth(l2, s+q+1);
		LCT::cut(c1); LCT::cut(c2); LCT::link(l1, c2);
		LCT::cut(c3); LCT::link(l2, c1); LCT::link(l3, c3);
	}
	inline int Q0(node *x) {
		access(x); splay(x); return x->s0;
	}
	inline int Q0(int x) {
		return Q0(ns+x);
	}
	inline int Q1(node *x, node *y) {
		int ans = 0;
		access(x), access(y), splay(x);
		if (x->f) ans = x->s1;
		access(x); splay(y);
		if (y->f) ans += y->s1;
		return ans;
	}
	inline int Q1(int x, int y) {
		return Q1(ns+x, ns+y);
	}
}
int main() {
	R(n); R(m);
	int k, t, x, y, p, q, c;
	LCT::node *last;
	for (int i=1; i<=n; ++i) {
		LCT::ns[n+i].key = 1;
		LCT::link(LCT::ns+i, last = LCT::ns+n+i);
		R(k);
		while (k--) {
			R(x);
			LCT::link(last, LCT::ns+x);
			last = LCT::ns+x;
		}
		LCT::link(last, LCT::ns+n+n+i);
	}
	while (m--) {
		R(t);
		if (t == 1) {
			R(x); R(p); R(c); R(y); R(q);
			LCT::M(x, p, c, y, q);
		} else
		if (t == 2) {
			R(x); R(y);
			printf("%d\n", LCT::Q1(x, y));
		} else
		if (t == 3) {
			R(x);
			printf("%d\n", LCT::Q0(x) - 1);
		}
	}
	return 0;
}
