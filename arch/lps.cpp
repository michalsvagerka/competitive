#include "../l/lib.h"
#include "../l/suffixarray.h"

class lps {
public:
	void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		string S; cin >> S;
		N = S.size();
		S.push_back('$');
		S.push_back('#');
		S += S;
		reverse(S.begin() + N + 1, S.end() - 1);

		cerr << S << endl;
		SuffixArray<int, true, true> SA(S);
		/*for (int j = 0; j < SA.N; ++j) {
			cerr << (j != SA.N-1 ? SA.LCP[j] : -1) << ' ' << S.c_str() + SA.S[j] << '\n';
		}*/
		int ans = 0;
		for (int i = 0; i < N; ++i) {
			assert(S[i] == S[2*N-i+1]);
			ans = max(ans, 2*SA.lcp(i, 2*N-i+1)-1);
			ans = max(ans, 2*SA.lcp(i, 2*N-i+2));
		}
		cout << ans << endl;

	}
};
