#include "../l/lib.h"
// #include "../l/mod.h"

class relenc {
public:
	void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		vector2<bool> V(N, N, false);
		vector<pii> A(N);
		vector<int> H(N), K(N,0);
		for (int i = 0; i < N; ++i) {
			A[i].y = i;
			for (int j = 0; j < N; ++j) {
				char c; cin >> c;
				if (c == '1') {
					V[i][j] = true;
					A[i].x++;
				}
			}
		}

		sort(A.begin(), A.end());
		for (int i = 0; i < N; ++i) {
			int k = A[i].y;
			H[k] = N-i;
			for (int j = 0; j < N; ++j) if (V[k][j] && K[j] == 0) K[j] = N-i;
		}

		bool ok = true;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				ok &= (V[i][j] == H[i] <= K[j]);
			}
		}

		if (ok) {
			cout << "YES\n" << H << K;
		} else {
			cout << "NO\n";
		}

	}
};
