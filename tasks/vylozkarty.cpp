#include "../l/lib.h"
#include "../l/tree.h"
// #include "../l/mod.h"

class vylozkarty {
public:
	int N, M, K;
	vector<int> A;
	unordered_map<int, vector<int>> L;

	bool can_solve(int R) {
		Fenwick<int> F(N, 0);
		for (int i = R; i > 0; --i) {
			int pos = -1;
			for (int j = L[i].size()-1; j >= 0; --j) {
				if (F.sum(L[i][j]) <= K-1) {
					pos = L[i][j];
					break;
				}
			}
			if (pos == -1) return false;
			F.add(pos, 1);
		}

		return true;
	}

    void solve(istream& cin, ostream& cout) {
		int T; cin >> T;
		for (int t = 0; t < T; ++t) {
			cin >> N >> M >> K;
			L.clear();
			A.resize(N); cin >> A;
			for (int i = 0; i < N; ++i) {
				L[A[i]].push_back(i);
			}

			cout << bsh(0, min(N, M), [&](int x) { return can_solve(x); }) << '\n';
		}
    }
};
