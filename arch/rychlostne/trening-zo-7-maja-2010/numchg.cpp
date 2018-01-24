#include "../l/lib.h"
// #include "../l/mod.h"

class numchg {
public:
	size_t N;
	vector<int> A,B;

	int find(size_t i, int chg) {
		if (i == N) {
			for (size_t j = 0; j < N; ++j) chg += abs(A[j] - B[j]);
			return chg;
		}
		int ans = find(i+1, chg);
		for (int j = 0; j < N; ++j) {
			if (j != i) {
				swap(A[i], A[j]);
				ans = min(ans, find(i+1, chg+1));
				swap(A[i], A[j]);
			}
		}
		return ans;
	}

	void solve(istream& cin, ostream& cout) {
		string S, T; cin >> S >> T;
		N = S.size();
		A.resize(N); B.resize(N);
		for (int i = 0; i < N; ++i) {
			A[i] = S[i] - '0';
			B[i] = T[i] - '0';
		}
		cout << find(0, 0) << endl;
	}
};
