#include "../l/lib.h"
// #include "../l/mod.h"

class plowing {
public:
	void solve(istream& cin, ostream& cout) {
		int N, I; cin >> N >> I;
		vector2<int> F(N,N,0);
		vector2<int> RF(N,N,0), CF(N,N,0), RB(N,N,0), CB(N,N,0);
		for (int i = 0; i < I; ++i) {
			int r,c,f; cin >> r >> c >> f; --r; --c;
			F[r][c] = f;
		}

		for (int i = 0; i < N; ++i) {
			int c = 0, b = 0;
			for (int j = 0; j < N; ++j) {
				c = max(0, c+F[i][j]);
				RF[i][j] = b = max(b, c);
			}

			c = 0; b = 0;
			for (int j = 0; j < N; ++j) {
				c = max(0, c+F[i][N-1-j]);
				RB[i][N-1-j] = b = max(b, c);
			}

			c = 0; b = 0;
			for (int j = 0; j < N; ++j) {
				c = max(0, c+F[j][i]);
				CF[j][i] = b = max(b, c);
			}

			c = 0; b = 0;
			for (int j = 0; j < N; ++j) {
				c = max(0, c+F[N-1-j][i]);
				CB[N-1-j][i] = b = max(b, c);
			}
		}

		int ans = max(F[0][0], 0);
		for (int r = 0; r < N; ++r) {
			for (int c = 0; c < N; ++c) {
				if (c > 0) ans = max(ans, CF[N-1][c] + RF[r][c-1]);
				if (c < N-1) ans = max(ans, CF[N-1][c] + RB[r][c+1]);
				if (r > 0) ans = max(ans, RF[r][N-1] + CF[r-1][c]);
				if (r < N-1) ans = max(ans, RF[r][N-1] + CB[r+1][c]);
			}
		}
		cout << ans << endl;
	}
};
