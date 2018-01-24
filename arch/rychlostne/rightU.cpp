#include "../l/lib.h"
// #include "../l/mod.h"

class rightU {
public:
    void solve(istream& cin, ostream& cout) {
		int N=$;
		vector<pii> P(N);
		for (pii&p:P) p = $;
		ll ans = 0;
		for (int i = 0; i < N; ++i) {
			map<pii, int> C;
			for (int j = 0; j < N; ++j) {
				if (i==j) continue;
				pii r = {P[j].x - P[i].x, P[j].y - P[i].y};
				int g = gcd(abs(r.x), abs(r.y));
				r.x /= g; r.y /= g;
				ans += C[{r.y, -r.x}] + C[{-r.y, r.x}];
				C[r]++;
			}
		}
		cout << ans << endl;
    }
};
