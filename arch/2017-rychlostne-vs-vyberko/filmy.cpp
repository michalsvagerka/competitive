#include "../l/lib.h"
#include "../l/tree.h"

class filmy {
public:
    void solve(istream& cin, ostream& cout) {
		int F,P; cin >> P >> F;
		vector<int> O(P); cin >> O;
		for (int&o:O) --o;

		vector<int> L(F); cin >> L;
		vector<int> N(P, P);
		vector<int> I(F, P);
		vector<bool> R(P, true);
		for (int i = P-1; i >=0; --i) {
			if (I[O[i]] != P) {
				N[i] = I[O[i]];
				R[I[O[i]]] = false;
			}
			I[O[i]] = i;
		}

		AddMaxTree<ll> T;
		T.setup(P, 0);
		for (int i = 0; i < P; ++i) {
			if (R[i]) {
				T.put(i, N[i]-1, L[O[i]]);
			}
		}
		ll ans = T.get(0, P-1);
		for (int i = 0; i < P; ++i) {

//			for (int j = i; j < P; ++j) {
//				cerr << T.get(j) << ' ';
//			} cerr << endl;
			T.put(i, N[i]-1, -L[O[i]]);
			if (N[i] != P) {
				T.put(N[i], N[N[i]]-1, L[O[i]]);
				ans = max(ans, T.get(0, P-1));
			}
		}
		cout << ans << endl;
	}
};
