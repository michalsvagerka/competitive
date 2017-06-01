#include "../l/lib.h"
// #include "../l/mod.h"

class crabbles {
public:
	set<ll> W;
	vector<pii> L;

	int best(int i, int P, int s, ll w) {
		if (i == P) {
			return W.find(w) != W.end() ? s : 0;
		}

		return max(best(i+1, P, s, w), best(i+1, P, s+L[i].y, w*27+L[i].x));
	}

    void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		for (int i = 0; i < N; ++i) {
			string s; cin >> s;
			if (s.size() > 10) continue;
			sort(s.begin(), s.end());
			ll w = 0;
			for (char c:s) w = w*27 + 1+c-'a';
			W.insert(w);
		}
		int M; cin >> M;
		for (int i = 0; i < M; ++i) {
			int P; cin >> P;
			L.clear();
			for (int j = 0; j < P; ++j) {
				char c; int q; cin >> c >> q;
				L.push_back({1+c-'a', q});
			}
			sort(L.begin(), L.end());
			cout << best(0, P, 0, 0LL) << '\n';
		}

    }
};
