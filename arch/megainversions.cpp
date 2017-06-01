#include "../l/lib.h"
#include "../l/tree.h"

class megainversions {
public:

	void solve(istream& cin, ostream& cout) {
		size_t N; cin >> N;
		vector<size_t >A(N); cin >> A;

		vector<int> M(N), Q(N);
		AddSumTree<int> T,R;
		T.setup(N+3, 0);
		R.setup(N+3, 0);
		for (int i = 0; i < N; ++i) {
			M[i] = T.get(A[i]+1, N+1);
			T.put(A[i], 1);
		}

		for (int i = N-1; i >= 0; --i) {
			Q[i] = R.get(0, A[i]-1);
			R.put(A[i], 1);
		}

		ll ans = 0;
		for (int i = 0; i < N; ++i) {
			ans += (ll)M[i] * Q[i];
		}

		cout << ans << endl;
	}
};
