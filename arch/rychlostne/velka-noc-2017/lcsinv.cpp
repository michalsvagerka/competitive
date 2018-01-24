#include "../l/lib.h"
// #include "../l/mod.h"

class lcsinv {
public:
    void solve(istream& cin, ostream& cout) {
		int N, L; cin >> N >> L;
		if (L > N) { cout << "IMPOSSIBLE\n" << endl; return; }
		string S; cin >> S;
		if (L == N) { cout << S << endl; return; }
		vector<int> C(26,0);
		for(char s:S) C[s-'a']++;
		pair<int,char> M{C[0], 'a'};
		for (int i = 0; i < 26; ++i) M=min(M, {C[i], 'a'+i});

		if (L < M.x) { cout << "IMPOSSIBLE\n" << endl; return; }

		stringstream ans;
		int i = 0;
		while (i < N && L > M.x) {
			ans << S[i];
			if (S[i] == M.y) --M.x;
			--L;
			++i;
		}

		while (i++ < N) ans << M.y;

		cout << ans.str() << endl;
    }
};
