#include "../l/lib.h"
// #include "../l/mod.h"

class semafory {
public:
    void solve(istream& cin, ostream& cout) {
		int N, K; cin >> N >> K;
		if (N == 1) {
			cout << 1 << endl;
			return;
		}

		vector<vector<int>> E(N);
		for (int i = 0; i < N - 1; ++i) {
			int u, v; cin >> u >> v;
			--u; --v;
			E[u].push_back(v);
			E[v].push_back(u);
		}

		vector<int> C(N);
		vector<int> O;
		for (int i = 0; i < N; ++i) {
			C[i] = E[i].size();
			if (C[i] == 1) O.push_back(i);
		}

		int ans = 0;
		while (K >= 2 && !O.empty()) {
			ans += O.size();
			K -= 2;

			vector<int> P;
			for (int o: O) {
				for (int p: E[o]) {
					if (--C[p] == 1) P.push_back(p);
				}
			}

			swap(O, P);
		}

		ans += min(K, (int)O.size());
		cout << ans << endl;
    }
};
