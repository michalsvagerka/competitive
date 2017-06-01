#include "../l/lib.h"
// #include "../l/mod.h"

class polygloti {
public:
    void solve(istream& cin, ostream& cout) {
		int N, J; cin >> N >> J;
		vector<set<int>> Q(J);
		vector2<int> F(J+N, J+N, MOD);
		for (int i = 0; i < N; ++i) {
			int q; cin >> q;
			for (int j = 0; j < q; ++j) {
				int p; cin >> p; Q[p-1].insert(i);
			}
			F[J+i][J+i] = 0;
		}

		for (int i = 0; i < J; ++i) {
			for (int j = i+1; j < J; ++j) {
				vector<int> I;
				set_intersection(Q[i].begin(), Q[i].end(), Q[j].begin(), Q[j].end(), back_inserter(I));
				if (!I.empty()) {
					F[i][j] = Q[j].size()-I.size();
					F[j][i] = Q[i].size()-I.size();
				}
			}

			for (int n:Q[i]) {
				F[J+n][i] = Q[i].size();
				F[i][J+n] = 0;
			}
		}

		for (int i = 0; i < J; ++i) {
			for (int j = 0; j < J + N; ++j) {
				if (F[j][i] == MOD) continue;
				for (int k = 0; k < J + N; ++k) {
					F[j][k] = min(F[j][k], F[j][i] + F[i][k]);
				}
			}
		}

		for (int i = J; i < J+N; ++i) {
			for (int j = J; j < J+N; ++j) {
				cout << (F[i][j] == MOD ? -1 : F[i][j]) << " \n"[j==J+N-1];
			}
		}

    }
};
