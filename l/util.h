#include "lib.h"

struct UnionFind {
	UnionFind(size_t N) : P(N, -1), comp(N) {}
	int find(int x) { while (P[x]>=0){x = P[x];}return x; }
	bool united(int x, int y) { return find(x) == find(y); }
	bool unite(int x, int y) { x=find(x);y=find(y);if(x==y){return false;}--comp;if(P[x]>P[y]){swap(x,y);}P[x]+=P[y];P[y]=x;return true;}
	vector<int> P;
	size_t comp;
};

/** Product of two 64-bit numbers modulo another. */
ull mulull(ull a, ull z, ull mod) {
#ifdef __SIZEOF_INT128__
	__int128 result = ((__int128) a * (__int128) z) % (__int128) mod;
	return (ull) result;
#else
    // schrage method
	ull q = mod / a, r = mod % a;
	ull rzq = (r < q) ? r * (z/q) : mulull(r, z/q, mod);
	ull azq = a * (z % q);
	if (azq >= rzq) return azq-rzq; else return azq-rzq+mod;
#endif
}

/** Multiply two 64-bit unsigned integers to get a 128-bit unsigned integer (as a pair of ull) */
pair<ull,ull> mulull(ull a, ull b) {
#ifdef __SIZEOF_INT128__
	__int128 result = (__int128) a * (__int128) b;
	return {(ull) (result >> 64), (ull) result};
#else
	ull c = (ui)a, d = a>>32, e = (ui)b, f = b>>32, g = d*f, h = d*e, i = f*c, j = c*e, k = (j>>32)+(ui)h+(ui)i, l = g+(h>>32)+(i>>32)+(k>>32);
	return {l, ((h+i) << 32) + j};
#endif
}

bool fractionGreaterOrEqual(ll a, ll b, ll c, ll d) {
	if (b < 0) { b = -b; a = -a; }
	if (d < 0) { d = -d; c = -c; }
	return a < 0 && c < 0 ? mulull(-a, d) <= mulull(-c, b) : (a >= 0) && (c < 0 || mulull(a, d) >= mulull(c, b));
}

bool fractionGreaterOrEqual(double a, double b, double c, double d) {
	return a/b >= c/d;
}

// this is based on modulus, but it's 2-3 times slower than the former
//bool fractionGreaterOrEqual(ll a, ll b, ll c, ll d) {
//	if (a<0 && c<0) return greaterOrEqual(-c,d,-a,b);
//	if (a<0) return false;
//	if (c<0) return true;
//	if (b==0) return true;
//	if (d==0) return false;
//	ll ab = a/b, cd = c/d;
//	if (ab > cd) return true;
//	if (ab < cd) return false;
//	return !greaterOrEqual(b, a%b, d, c%d);
//}


/** Computing lower and upper envelope. Useful for "convex hull trick". */
namespace Envelope {
	template<typename T>
	struct Line {
		T m, b;
		mutable function<const Line<T> *()> succ;

		bool operator<(const Line &rhs) const {
			if (rhs.b != numeric_limits<T>::min()) return m < rhs.m;
			const Line *s = succ();
			if (!s) return 0;
			return b - s->b < (s->m - m) * rhs.m;
		}
	};

	template<typename T>
	struct Upper : public multiset<Envelope::Line<T>> {
		using parent = multiset<Line<T>>;

		bool bad(typename parent::iterator y) {
			auto z = next(y);
			if (y == parent::begin()) {
				return z != parent::end() && y->m == z->m && y->b <= z->b;
			} else {
				auto x = prev(y);
				if (z == parent::end()) {
					return y->m == x->m && y->b <= x->b;
				} else {
					return fractionGreaterOrEqual(x->b - y->b, y->m - x->m, y->b - z->b, z->m - y->m);
				}
			}
		}

		void insert_line(T m, T b) {
			auto y = parent::insert({m, b});
			y->succ = [=] { return next(y) == parent::end() ? 0 : &*next(y); };
			if (bad(y)) { parent::erase(y); return; }
			while (next(y) != parent::end() && bad(next(y))) parent::erase(next(y));
			while (y != parent::begin() && bad(prev(y))) parent::erase(prev(y));
		}

		T operator[](T x) const {
			auto l = parent::lower_bound({x, numeric_limits<T>::min()});
			return l == parent::end() ? numeric_limits<T>::min() : l->m * x + l->b;
		}
	};

	template<typename T>
	struct Lower : public Upper<T> {
		void insert_line(T m, T b) { Upper<T>::insert_line(-m, -b); }
		T operator[](T x) const { return -Upper<T>::operator[](x); }
	};
}