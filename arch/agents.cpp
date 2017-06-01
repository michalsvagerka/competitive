#include "../l/lib.h"
// #include "../l/mod.h"

class agents {
public:
	void solve(istream& cin, ostream& cout) {
		int N; cin >> N; vector<int> A(N); cin >> A;
		vector<int> C(N,0);
		for(int&a:A){C[--a]++;};
		vector<int> M, W;
		for(int i=0;i<N;++i) if (!C[i]) W.push_back(i);
		int w = 0;
		int ans = 0;
		while (w < W.size()) {
			int m = A[W[w]];
			if (C[m] > 0) {
				++ans;
				C[m] = -1;
				if (!--C[A[m]]) W.push_back(A[m]);
			}
			w++;
		}
		for (int i = 0; i < N; ++i) {
			if (C[i] > 0) {
				int p = 1, c = A[i]; C[i] = -2;
				while (c != i) { C[c] = -2; ++p; c = A[c]; }
				ans += p / 2;
			}
		}
		cout << ans << endl;
	}
};
