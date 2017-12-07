#include "../l/lib.h"
#include "../l/mod.h"

class karavana1 {
public:
    void solve(istream& cin, ostream& cout) {
		int T; cin >> T;
		auto F = FieldMod::fact(20000);
		auto I = FieldMod::invfact(20000);
		for (int t = 0; t < T; ++t) {
			string S; cin >> S;
			ui N = S.size();
			vector<bool> U(26, false);
			for (int i = 0; i < N; ++i) {
				if (S[i]!='?') U[S[i]-'a'] = true;
			}

			ui unused = 26-count(U.begin(), U.end(), true);

			vector<FieldMod> ans(unused+1, 0);
			ans[0] = 1;
			int lastPos = -1;
			for (ui i = 0; i < N; ++i) {
				if (S[i] != '?') {

					if (lastPos == -1) {
						vector<FieldMod> next(unused+1, 0);
						for (int bef = 0; bef <= unused; ++bef) {
							for (int aft = bef; aft <= unused; ++aft) {
								if (aft - bef > i) break;
								next[aft] += ans[bef] * F[unused-bef] * I[unused-aft] * F[i] * I[i -aft+bef] * I[aft-bef];
							}
						}
						swap(next, ans);
					} else if (S[lastPos] != S[i]) {
						vector<FieldMod> next(unused+1, 0);

						for (int bef = 0; bef <= unused; ++bef) {
							for (int aft = bef; aft <= unused; ++aft) {
								if (aft - bef > i - lastPos - 1) break;
								next[aft] += ans[bef] * F[unused-bef] * I[unused-aft] * F[i - lastPos] * I[i - lastPos-aft+bef-1] * I[aft-bef+1];
							}
						}
						swap(next, ans);
					}
					lastPos = i;
				}
			}
			vector<FieldMod> next(unused+1, 0);
			if (lastPos == -1) {
				for (int aft = 1; aft <= unused && aft <= N; ++aft) {
					next[aft] += F[unused] * I[unused - aft] * F[N - 1] * I[aft-1] * I[N-aft];
				}
			} else {
				for (int bef = 0; bef <= unused; ++bef) {
					for (int aft = bef; aft <= unused; ++aft) {
						if (aft - bef > N - lastPos - 1) break;
						next[aft] += ans[bef] * F[unused - bef] * I[unused - aft] * F[N - lastPos - 1] *
									 I[N - 1 - lastPos - aft + bef] * I[aft - bef];
					}
				}
			}
			swap(next, ans);

			FieldMod tot = 0;
			for (auto&a: ans) tot += a;
			cout << tot << endl;
		}
    }
};
