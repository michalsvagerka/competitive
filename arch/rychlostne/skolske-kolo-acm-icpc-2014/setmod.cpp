#include "../l/lib.h"
// #include "../l/mod.h"

template <typename K, typename V> struct avlnode {
	avlnode(K k, V v) : l(0),r(0),h(1),s(1),k(k),v(v) {}
	~avlnode() { delete l; delete r; }
	int size() const { return s; }
	avlnode<K,V>*insert(K k, V v) {
        a();
		if (k<this->k) l=l?l->insert(k,v):new avlnode<K,V>(k,v);
		else if (k==this->k) return this;
		else r=r?r->insert(k,v):new avlnode<K,V>(k,v);
		return balance();
	}
	avlnode<K,V>* get(K k) {
        a();
		if (k<this->k) { return l ? l->get(k) : nullptr; }
		else if (k>this->k) { return r ? r->get(k) : nullptr; }
		else { return this; }
	};
//	ui smaller(K k) {
//        a();
//		if (k<this->k) return l ? l->smaller(k) : 0;
//		else {
//			ui s = l ? l->s : 0;
//			if (k==this->k) return s;
//			else return s+1+ (r?r->smaller(k):0);
//		}
//	};
	avlnode<K,V>* remove(K k) {
        a();
		if (k<this->k) { if(l) l = l->remove(k); else return this; }
		else if (k>this->k) { if (r) r = r->remove(k); else return this; }
		else if (!l) { avlnode<K,V>*t = r; r = nullptr; delete this; return t; }
		else if (!r) { avlnode<K,V>*t = l; l = nullptr; delete this; return t; }
		else { avlnode<K,V>* q = l; while (q->r) { q->a(); q = q->r; } this->k = q->k; this->v = q->v; l = l->remove(this->k); }
		return balance();
	};
	template<typename T> void foreach(T f) {a();if(l){l->foreach(f);}f(k,v);if(r){r->foreach(f);}}
	avlnode<K,V>* at(int c) {a();if (l) {if (l->s > c) return l->at(c); else c -= l->s;} return c ? r->at(c-1) : this; }
//	avlnode<K,V>* merge(avlnode<K,V> *n) {a();auto q = this; n->foreach([&q](K k,V v){ q=q->insert(k,v); }); return q; }
	void a(int q = 2) {
		if (q==0) return;
		k += v;
		if (l) {l->v += v; l->a(q-1);};
		if (r) {r->v += v; r->a(q-1);};
		v = 0;
	}
    K k;V v;

    void u() { s=(l?l->s:0)+(r?r->s:0)+1; h=max(l?l->h:0,r?r->h:0)+1; }
    avlnode<K,V>*rr() {a(); l->a(); if (l->r) l->r->a(); auto x = l; l = x->r; u(); x->r = this; x->u(); return x; }
    avlnode<K,V>*lr() {a(); r->a(); if (r->l) r->l->a(); auto y = r; r = y->l; u(); y->l = this; y->u(); return y; }
    int getBalance() const { return (l?l->h:0) - (r?r->h:0); }
	void mod(int a,int b, K d) {
		if (a <= 0 && b >= s) {
			v += d;
		} else {
			if (l) {
				if (a < l->s) l->mod(a, b, d);
				a -= l->s;
				b -= l->s;
			}

			if (a <= 0 && b > 0) k += d;
			--a;
			--b;

			if (r && b > 0) r->mod(a, b, d);
		}
	}
    avlnode<K,V>* balance() {
        a();
		int b = getBalance();
        if (b > 1) { if (l->getBalance() >= 0) return rr(); else { l = l->lr(); return rr(); } }
        if (b < -1) { if (r->getBalance() > 0) { r=r->rr(); return lr(); } else { return lr(); } }
        u(); return this;
    };
    avlnode<K,V> *l,*r;int h,s;
};
template<typename K,typename V>ostream& operator<<(ostream &os, const avlnode<K,V>& t) {os<<'<';if (t.l){os<<t.l<<',';}os<<'('<<t.k<<','<<t.v<<')';if(t.r){os<<','<<t.r;}os<<'>';return os;}

template<typename K, typename V> struct avl {
	avl() : r(0) {}
	~avl() { delete r; }
	avlnode<K,V>* get(K k) { return r?r->get(k):0; };
//	ui smaller(K k) { return r?r->smaller(k):0; }
	void insert(K k, V v) { r=r?r->insert(k,v):new avlnode<K,V>(k,v); };
	void remove(K k) { r=r?r->remove(k):r; }
	void mod(int a, int b, K d) { if (r) r->mod(a,b,d); }
	avlnode<K,V>* select(int c) { if (!r||r->s<=c||c<0) return 0; else return r->at(c); };
	int size() const { return r?r->s:0; }
//	template<typename T> void foreach(T f) {if(r)r->foreach(f);}
	avlnode<K,V> *r;
};

class setmod {
public:
    void solve(istream& cin, ostream& cout) {
		int M; cin >> M;
		avl<ll,ll> A;
		for (int i = 0; i < M; ++i) {
			int t; cin >> t;
			if (t == 1) {
				int k; cin >> k;
				while (k--) {
					ll v; cin >> v;
					A.insert(v,0);
				}
				cout << A.size() << '\n';
			} else if (t == 2) {
				int n = A.size();
				int r = (n-1)/2;
				ll k = A.select(r)->k;
				A.remove(k);
				cout << k << '\n';
			} else {
				int a, b; cin >> a >> b;
				ll d = A.select(b)->k - A.select(b-1)->k - 1;
				if (d) A.mod(a,b,d);
				cout << d << '\n';
			}

		}
    }
};
