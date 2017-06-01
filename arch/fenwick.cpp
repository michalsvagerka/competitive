#include "../l/lib.h"
#include "../l/tree.h"

class fenwick {
public:
	void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		Fenwick<ll> F(N, 0LL);
		vector<ll> A(N); cin >> A;
		for (int i = 0; i < N-1; ++i) {
			if (i%2==0){
				A[i] = -F.F[i+1];
			}
			F.add(i, A[i]);
		}
		F.add(N-1, A[N-1]);
		cout << A;
	}
};
