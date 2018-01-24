#include "../l/lib.h"
// #include "../l/mod.h"

class deposits {
public:
    void solve(istream& cin, ostream& cout) {
		int r = 1000000;
		vector<int> A(r+1,0), B(r+1,0);
		int N; cin >> N;
		for (int i = 0; i < N; ++i) {
			int a; cin >> a; A[a]++;
		}

		int M; cin >> M;
		for (int i = 0; i < M; ++i) {
			int a; cin >> a; B[a]++;
		}

		ll ans = 0;
		for (int i = 1; i <= r; ++i) {
			if (B[i]) {
				for (int j = i; j <= r; j+=i) {
					ans += (ll)B[i] * A[j];
				}
			}
		}
		cout << ans << endl;

	}
};
