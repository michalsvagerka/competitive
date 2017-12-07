#include "../l/lib.h"
// #include "../l/mod.h"

class minhra {
public:
    void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		set<int> Q;
		for (int i = 0; i < N; ++i) {
			int x; cin >> x; Q.insert(x);
		}
		ll best = 0;
		for (int q : Q) best = max(best, q - best);
		cout << best << endl;
    }
};
