#include "../l/lib.h"
#include "../l/mod.h"


typedef Field<1000000009> F;
class school {
public:
	void solve(istream& cin, ostream& cout) {
		int MAX = 4000;
		vector<bool> S(MAX*MAX, true);
		for (int i = 2; i < MAX; ++i) {
			if (S[i]) {
				for (int j = i*i; j < MAX*MAX; j+=i) {
					S[j] = false;
				}
			}
		}

		vector<int> P;
		vector<F> PS{0};
		for (int i = 2; i < MAX*MAX; ++i) {
			if (S[i]) {
				P.push_back(i);
				PS.push_back(PS.back() + i);
			}
		}

		int N, M;
		cin >> N >> M;
		F Ans = 0;
		for (int i = 0; i < N; ++i) {
			Ans += P[i] * (F(2) * F(i+1) * F(N-i) - 1);
		}

		for (int i = 0; i < M; ++i) {
			int r, c; cin >> r >> c;
			if (r > c) swap(r,c);
			Ans -= PS[c] - PS[r-1];
		}

		cout << Ans << endl;
	}
};
