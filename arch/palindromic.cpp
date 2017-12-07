#include "../l/lib.h"
#include "../l/mod.h"

class palindromic {
public:
    void solve(istream& cin, ostream& cout) {
		string S; cin >> S;
		ui N = S.size();
		vector2<Field<1000000009>> R(N+1, N, 0);
		fill(R[1].begin(), R[1].end(), 1);

		for (int l = 2; l <= N; ++l) {
			for (int i = 0; i + l <= N; ++i) {
				R[l][i] = R[l-1][i] + R[l-1][i+1] - R[l-2][i+1];
				if (S[i] == S[i + l - 1]) R[l][i] += R[l-2][i+1] + 1;
			}
		}

		cout << R[N][0] << endl;
    }
};
