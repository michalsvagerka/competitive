#include "../l/lib.h"
// #include "../l/mod.h"

class multiples {
public:
	vector<bool> D;

	ll dp(ll X, ll upTo) {
		vector3<ll> R(13, X, 4, 0);
		R[0][0][0] = 1;
		for (int i = 0; i < 12; ++i) {
			ll dig = upTo;
			for (int j = i; j < 11; ++j) {
				dig /= 10;
			}
			dig %= 10;
			for (int j = 0; j < X; ++j) {
				for (int k = 0; k < 4; ++k) {
					if (!R[i][j][k]) continue;
					bool hasStarted = (k & 1) == 1;
					bool isLower = (k & 2) == 2;
					if (!hasStarted || D[0]) {
						R[i+1][(10*j)%X][hasStarted | ((isLower || dig > 0) << 1)] += R[i][j][k];
					}

					for (int d = 1; d < 10; ++d) {
						if (!D[d]) continue;
						if (!isLower && d > dig) break;
						R[i+1][(10*j+d)%X][1 | ((isLower || d < dig) << 1)] += R[i][j][k];
					}
				}
			}
		}
		return R[12][0][0] + R[12][0][1] + R[12][0][2] + R[12][0][3];
	}

	bool correctDigits(ll V) {
		while (V > 0) {
			int d = V%10;
			if (!D[d]) return false;
			V /= 10;
		}
		return true;
	}

    void solve(istream& cin, ostream& cout) {
		ll X, A, B; cin >> X >> A >> B;
		D=vector<bool>(10, false);
		string S; cin >> S;
		for(char s:S) D[s-'0'] = true;
		if (X <= 100000) {
			cout << dp(X, B) - dp(X, A-1) << endl;
		} else {
			int ans = 0;
			for (int i = 1 + (A-1) / X; i <= B / X; ++i) {
				if (correctDigits(i*X)) {
					++ans;
				}
			}
			cout << ans << endl;
		}
    }
};
