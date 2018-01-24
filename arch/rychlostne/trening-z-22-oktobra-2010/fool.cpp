#include "../l/lib.h"
// #include "../l/mod.h"

class fool {
public:
	void solve(istream& cin, ostream& cout) {
		int T; cin >> T;
		for (int t = 0; t < T; ++t) {
			string str; cin >> str;
			int N = str.size();
			vector2<bool> S(N,N),L(N,N),E(N,N);
			for (int l = 0; l < N; ++l) {
				for (int b = 0; b < N-l; ++b) {
					S[l][b] = str[b] == '{' && str[b+l] == '}' && (l==1 || L[l-2][b+1]);
					E[l][b] = (l == 0 || S[l][b]);
					L[l][b] = E[l][b];
					for (int k = 0; k < l-1 && !L[l][b]; ++k) {
						L[l][b] = E[k][b] && L[l-k-2][b+k+2] && str[b+k+1] == ',';
					}
				}
			}
			cout << "Word #" << t+1 << ": " << (S[N-1][0] ? "" : "No ") << "Set\n";
		}
	}
};
