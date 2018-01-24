#include "../l/lib.h"
// #include "../l/mod.h"

class muffiny {
public:
	void solve(istream& cin, ostream& cout) {
		int N, X; cin >> N >> X;
		vector<int> A(N); cin >> A;
		maxheap<int> Q;
		Q.push(0);
		while (N%X) Q.push(A[--N]);
		ll ans = Q.top(); Q.pop();
		while (N > 0) {
			for (int i = 0; i < X; ++i) Q.push(A[--N]);
			ans += Q.top(); Q.pop();
		}
		cout << ans << endl;
	}
};
