#include "../l/lib.h"
// #include "../l/mod.h"

class multiples {
public:
	ll calc_dp(int X, ll U, vector<bool> &R) {
		vector2<pair<ll,ll>> D(12, X, {0LL,0LL});
		D[0][0] = {1,0};
		for (int i = 1; i <= 11; ++i) {
			ll p = 1;
			for (int j = i; j < 11; ++j) p*=10;
			int d = U / p % 10;
			for (int k = 0; k < X; ++k) {
				cerr << D[i-1][k].x << ' ' << D[i-1][k].y << endl;
				for (int j = 0; j < d; ++j) {
					if (R[j]) D[i][(10*k+j)%X].y += D[i-1][k].x;
				}
				if (R[d]) D[i][(10*k+d)%X].x += D[i-1][k].x;
				for (int j = 0; j <= 9; ++j) {
					if (R[j]) D[i][(10*k+j)%X].y += D[i-1][k].y;
				}
			}
		}
		return D[11][0].x + D[11][0].y;
	}

    void solve(istream& cin, ostream& cout) {
		ll X=$,A=$,B=$;
		string S=$;
		vector<bool> R(10, false);
		for (char c:S) R[c-'0']=true;
		ll ans = 0;
		if (X >= 10000) {
			for (ll i = 1; i*X <= B; ++i) {
				if (X*i >= A) {
					ll y = X*i;
					bool ok = true;
					while (y) {
						ok &= R[y%10];
						y /= 10;
					}
					ans += ok;
				}
			}
		} else {
			ans = calc_dp(X, B, R) - calc_dp(X, A-1, R);
		}

		cout << ans << endl;
    }
};
