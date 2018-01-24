#include "../l/lib.h"
// #include "../l/mod.h"

class allcake2 {
public:
    void solve(istream& cin, ostream& cout) {
		int A,B,N; ll K; cin >> A >> B >> N >> K;
		vector<int> X(N+2,0), Y(N+2,0);
		for (int i = 0; i < N; ++i) cin >> X[i+1];
		for (int i = 0; i < N; ++i) cin >> Y[i+1];
		X[N+1] = A; Y[N+1] = B;
		vector<int> YL(N+1), XL(N+1);
		for (int i = 0; i < N+1; ++i) YL[i] = Y[i+1] - Y[i];
		for (int i = 0; i < N+1; ++i) XL[i] = X[i+1] - X[i];
		sort(XL.begin(), XL.end());
		sort(YL.begin(), YL.end(), greater<int>());
		ll ans = bsh(0LL, (ll)A*B, [&](ll x) {
			ll r = 0; int j = 0;
			for (int i = 0; i <= N; ++i) {
				while (j <= N && (ll)YL[j] * XL[i] >= x) ++j;
				r += j;
			}
			return r>=K;
		});
		cout << ans << endl;
    }
};
