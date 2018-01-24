#include "../l/lib.h"
// #include "../l/mod.h"

class vahydarcekov {
public:
	vector<int> P;
	vector<ll> R;

	pair<int, ll> find(int u) {
		ll d = 0;
		while (P[u] >= 0) {
			d += R[u];
			u = P[u];
		}
		return {u,d};
	};

	void solve(istream& cin, ostream& cout) {
		int D, U;
		cin >> D >> U;
		P = vector<int>(D, -1);
		R = vector<ll>(D, 0);

		for (int i = 0; i < U; ++i) {
			char c;
			cin >> c;
			int u, v;
			cin >> u >> v;
			--u;
			--v;
			auto fu = find(u);
			auto fv = find(v);

			if (c == '!') {
				int d;
				cin >> d;
				if (fu.x != fv.x) {
					if (P[fu.x] > P[fv.x]) {
						swap(fu, fv);
						d = -d;
					}
					P[fu.x] += P[fv.x];
					P[fv.x] = fu.x;
					R[fv.x] = -fv.y + fu.y - d;
				}
			} else {
				if (fu.x == fv.x) {
					cout << fu.y - fv.y << '\n';
				} else {
					cout << "UNKNOWN\n";
				}
			}

		}

	}
};
