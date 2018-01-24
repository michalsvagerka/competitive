#include "../l/lib.h"
// #include "../l/mod.h"

class batohy {
public:
    void solve(istream& cin, ostream& cout) {
		int V,B; cin >> V >> B;
		vector<int> W(V);
		vector<int> C(B);
		cin >> W >> C;
		sort(C.begin(), C.end(), greater<int>());
		if (B > V) C.resize(V);

		vector<ll> T(1<<V, 0);
		for (int i = 0; i < V; ++i) {
			for (int j = 0; j < (1<<i); ++j) {
				T[(1<<i) | j] = T[j] + W[i];
			}
		}
		cout << T;

    }
};
