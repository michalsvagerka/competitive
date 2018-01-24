#include "../l/lib.h"
// #include "../l/mod.h"

class lineup {
public:
	void solve(istream& cin, ostream& cout) {
		int N, K; cin >> N >> K;
		vector<int> C(K, 0);
		map<vector<int>, int> I{{C,-1}};
		int best = 0;
		for (int i = 0; i < N; ++i) {
			int F; cin >> F;
			bool zero = false;
			for (int j = 0; j < K; ++j) zero |= (C[j] += (F & (1 << j)) != 0) == 0;
			if (!zero) for (int j = 0; j < K; ++j) --C[j];
			auto iter = I.find(C);
			if (iter != I.end()) {
				best = max(best, i - iter->second);
			} else {
				I[C] = i;
			}
		}
		cout << best << endl;
	}
};
