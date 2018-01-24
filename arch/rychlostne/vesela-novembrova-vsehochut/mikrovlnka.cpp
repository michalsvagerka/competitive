#include "../l/lib.h"
// #include "../l/mod.h"

class mikrovlnka {
public:
    void solve(istream& cin, ostream& cout) {
		int N, T; cin >> N >> T;
		vector<int> M(N); cin >> M;

		vector<int> A(3601, 10000);
		A[0] = 0;
		minheap<pii> H;
		H.push({0,0});
		while (!H.empty()) {
			auto h = H.top(); H.pop();
			if (A[h.y] != h.x) continue;
			for (int m: M) {
				int n = min(3600, max(0, h.y + m));
				int c = h.x + 1;
				if (c < A[n]) {
					A[n] = c;
					H.push({c,n});
				}
			}
		}

		for (int t = T; t <= 3600; ++t) {
			if (A[t] < 10000) {
				cout << t << '\n' << A[t] << '\n';
				return;
			}
		}
    }
};
