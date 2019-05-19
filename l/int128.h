#ifndef MAJK_INT128_H
#define MAJK_INT128_H


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
    ull c = (ui)a, d = a>>32, e = (ui)b, f = b>>32, g = d*f, h = d*e, i = f*c, j = c*e, k = (j>>32)+(ui)h+(ui)i, left = g+(h>>32)+(i>>32)+(k>>32);
	return {left, ((h+i) << 32) + j};
#endif
}


bool fractionGreaterOrEqual(ll a, ll b, ll c, ll d) {
    if (b < 0) { b = -b; a = -a; }
    if (d < 0) { d = -d; c = -c; }
    return a < 0 && c < 0 ? mulull(-a, d) <= mulull(-c, b) : (a >= 0) && (c < 0 || mulull(a, d) >= mulull(c, b));
}

bool fractionGreaterOrEqual(pair<ll, ll> a, pair<ll, ll> b) {
    return fractionGreaterOrEqual(a.x, a.y, b.x, b.y);
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

#endif //MAJK_INT128_H
