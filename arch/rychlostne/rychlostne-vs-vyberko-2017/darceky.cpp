#include "../l/lib.h"
#include "../l/mod.h"

class darceky {
public:
    void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		vector<int> X(N); cin >> X;
		sort(X.begin(), X.end(), greater<int>());
		FieldMod ans = 1;
		int c = 0, j = 0;
		for (int i = 0; i < N; ++i) {
			while (j < N && X[j] >= N-i) ++j;
			if (j <= i) { cout << 0 << endl; return; }
			ans *= j-i;
		}
		cout << ans << endl;
    }
};
