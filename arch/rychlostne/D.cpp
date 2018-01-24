#include "../l/lib.h"
// #include "../l/mod.h"

class D {
public:
    void solve(istream& cin, ostream& cout) {
		int T; cin >> T;
		for (int t = 0; t < T; ++t) {
			int N, K; cin >> N >> K;
			cout << min(N, K-1) << "\n";
		}
    }
};
