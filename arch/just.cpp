#include "../l/lib.h"
// #include "../l/mod.h"

class just {
public:
    void solve(istream& cin, ostream& cout) {
		ll N; cin >> N;
		ll ans = 0;
		for (int i = 1; i <= 13*9; ++i) {
			vector3<pair<ll,ll>> D(14, 13*9+1, i, {0LL,0LL});
			D[0][0][0] = {1,0};
			for (int j = 0; j < 13; ++j) {
				ll p = 1;
				for (int m = 1; m < 13-j; ++m) {
					p *= 10;
				}
				int d = N / p % 10;

				for (int k = 0; k < 13*9+1; ++k) {
					for (int m = 0; m < i; ++m) {
						if (D[j][k][m] == pair<ll,ll>{0LL,0LL}) continue;

						for (int l = 0; l < d; ++l) {
							D[j + 1][k + l][(10*m+l)%i].y += D[j][k][m].x;
						}
						D[j + 1][k + d][(10*m+d)%i].x += D[j][k][m].x;

						for (int l = 0; l < 10; ++l) {
							D[j+1][k+l][(10*m+l)%i].y += D[j][k][m].y;
						}
					}
				}
			}
			ans += D[13][i][0].x + D[13][i][0].y;
		}
		cout << ans << endl;
    }
};
