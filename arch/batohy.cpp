#include "../l/lib.h"
// #include "../l/mod.h"

class batohy {
public:
    void solve(istream& cin, ostream& cout) {
		int V, B; cin >> V >> B;
		int X = 1 << V;
		vector<int> W(V), C(B); cin >> W >> C;

		sort(C.begin(), C.end(), greater<int>());
		C.push_back(0);

		vector<pii> D(X, {B, 0});
		D[0] = {0, -C[0]};
		for (int m = 1; m < X; ++m) {
			for (int i = 0; i < V; ++i) {
				if ((1<<i) & m) {
					pii p = D[m^(1<<i)];
					if (-p.y >= W[i]) {
						D[m] = min(D[m], {p.x, W[i] + p.y});
					} else if (C[p.x+1] >= W[i]) {
						D[m] = min(D[m], {p.x+1, W[i] - C[p.x+1]});
					}
				}
			}
		}

		if (D[X-1].x == B) {
			cout << "NIE\n";
		} else {
			cout << D[X-1].x+1 << endl;
		}
    }
};
