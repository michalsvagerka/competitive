#include "../l/lib.h"
// #include "../l/mod.h"



class intpower {
public:
	vector<int> M;
	vector<ll> P;

	ll n_root(ll x, int n) {
		ll r = bsh(0LL, P[n], [=](ll y){ll q=1;for(int i=0;i<n;++i){q*=y;}return q<=x;});
		return r;
	}

	ll calc(ll a) {
		ll ans = 0;
		for (int i = 1; i <= 61; ++i) {
			ans += M[i] * n_root(a, i);
		}
		return ans;
	}

	void solve(istream& cin, ostream& cout) {
		M = vector<int>(62, 0);
		P = vector<ll>(62, 0);
		for (int i = 1; i <= 61; ++i) {
			M[i] = i;
			for (int j = 1; j < i; ++j) if (i%j == 0) M[i] -= M[j];
			P[i] = (ll)(floor(pow(1LL<<62, 1./i)));
		}
		int T; cin >> T;
		for (int t = 0; t < T; ++t) {
			ll a,b; cin >> a >> b;
			cout << calc(b) - calc(a-1) << endl;
		}
	}
};
