#include "../l/lib.h"
// #include "../l/mod.h"

class veze3 {
public:
    void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		vector<int> A(N); cin >> A;
		int ans = N;
		for (int i = 0; i < N; ++i) {
			if (A[i] < i+1) {
				ans = i;
				break;
			}
		}
		cout << ans << '\n';
		for (int j = 1; j <= ans; ++j) {
			cout << j << ' ' << j << '\n';
		}
    }
};
