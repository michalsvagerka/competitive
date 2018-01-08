template <typename K, typename V> struct avlnode {
	avlnode(K k, V v) : l(0),r(0),h(1),s(1),k(k),v(v) {}
	~avlnode() { delete l; delete r; }
	avlnode<K,V> *l,*r;int h,s;K k;V v;
	int size() const { return s; }
	void u() { s=(l?l->s:0)+(r?r->s:0)+1; h=max(l?l->h:0,r?r->h:0)+1; }
	avlnode<K,V>*rr() {auto x = l; l = x->r; u(); x->r = this; x->u(); return x; }
	avlnode<K,V>*lr() {auto y = r; r = y->l; u(); y->l = this; y->u(); return y; }
	avlnode<K,V>*insert(K k, V v) {
		if (k<this->k) l=l?l->insert(k,v):new avlnode<K,V>(k,v);
		else r=r?r->insert(k,v):new avlnode<K,V>(k,v);
		return balance();
	}
	int getBalance() const { return (l?l->h:0) - (r?r->h:0); }
	avlnode<K,V>* get(K k) {
		if (k<this->k) { return l ? l->get(k) : nullptr; }
		else if (k>this->k) { return r ? r->get(k) : nullptr; }
		else { return this; }
	};
	int smaller(K k) {
		if (k<this->k) return l ? l->smaller(k) : 0;
		else {
			int s = l ? l->s : 0;
			if (k==this->k) return s;
			else return s+1+ (r?r->smaller(k):0);
		}
	};
	avlnode<K,V>* remove(K k) {
		if (k<this->k) { if(l) l = l->remove(k); else return this; }
		else if (k>this->k) { if (r) r = r->remove(k); else return this; }
		else if (!l) { avlnode<K,V>*t = r; r = nullptr; delete this; return t; }
		else if (!r) { avlnode<K,V>*t = l; l = nullptr; delete this; return t; }
		else { avlnode<K,V>* q = l; while (q->r) { q = q->r; } this->k = q->k; this->v = q->v; l = l->remove(this->k); }
		return balance();
	};
	avlnode<K,V>* balance() {
		int b = getBalance();
		if (b > 1) { if (l->getBalance() >= 0) return rr(); else { l = l->lr(); return rr(); } }
		if (b < -1) { if (r->getBalance() > 0) { r=r->rr(); return lr(); } else { return lr(); } }
		u(); return this;
	};
	template<typename T> void foreach(T f) {if(l){l->foreach(f);}f(k,v);if(r){r->foreach(f);}}
	avlnode<K,V>* at(int c) {if (l) {if (l->s > c) return l->at(c); else c -= l->s;} return c ? r->at(c-1) : this; }
	avlnode<K,V>* merge(avlnode<K,V> *n) {auto q = this; n->foreach([&q](K k,V v){ q=q->insert(k,v); }); return q; }
};
template<typename K,typename V>ostream& operator<<(ostream &os, const avlnode<K,V>& t) {os<<'<';if (t.l){os<<t.l<<',';}os<<'('<<t.k<<','<<t.v<<')';if(t.r){os<<','<<t.r;}os<<'>';return os;}

template<typename K, typename V> struct avl {
	avl() : r(0) {}
	~avl() { delete r; }
	avlnode<K,V>* get(K k) { return r?r->get(k):0; };
	int smaller(K k) { return r?r->smaller(k):0; }
	void insert(K k, V v) { r=r?r->insert(k,v):new avlnode<K,V>(k,v); };
	void remove(K k) { r=r?r->remove(k):r; }
	avlnode<K,V>* select(int c) { if (!r||r->s<c||c<0) return 0; else return r->at(c); };
	int size() const { return r?r->s:0; }
	template<typename T> void foreach(T f) {if(r)r->foreach(f);}
	avlnode<K,V> *r;
};