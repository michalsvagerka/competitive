#include "../l/lib.h"
// #include "../l/mod.h"

class konik {
public:

	void solve(istream& cin, ostream& cout) {
		int N; cin >> N;
		int R,C; cin >> R >> C; --R; --C;
		vector2<int> B(N,N);
		vector<pair<int, pii>> Q;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				int b; cin >> b;
				B[i][j] = b;
				Q.push_back({b, {i,j}});
			}
		}
		sort(Q.begin(), Q.end());

		vector2<int> V(N,N,-1000000000);
		vector<vector<pii>> row(N), column(N);

		int prev = -1;
		vector<pii> commit;
		for (auto q:Q) {
			int r = q.y.x, c = q.y.y, v = q.x;
			if (v > prev) {
				for (pii com:commit) {
					row[com.x].push_back({V[com.x][com.y], com.y});
					sort(row[com.x].begin(), row[com.x].end(), greater<pii>());
					if (row[com.x].size() > 6) row[com.x].resize(6);

					column[com.y].push_back({V[com.x][com.y], com.x});
					sort(column[com.y].begin(), column[com.y].end(), greater<pii>());
					if (column[com.y].size() > 6) column[com.y].resize(6);
				}
				commit.clear();
				prev = v;
			}

			if (r==R && c==C) {
				V[R][C] = 1;
				commit.push_back({R,C});
				continue;
			}


			int cur = -1000000000;
			if (r > 0) {
				for (auto it = row[r - 1].begin(); it != row[r - 1].end(); ++it) {
					if (abs(it->y - c) > 1) {
						cur = max(cur, it->x + 1);
						break;
					}
				}
			}
			if (r < N - 1) {
				for (auto it = row[r + 1].begin(); it != row[r + 1].end(); ++it) {
					if (abs(it->y - c) > 1) {
						cur = max(cur, it->x + 1);
						break;
					}
				}
			}
			if (c > 0) {
				for (auto it = column[c - 1].begin(); it != column[c - 1].end(); ++it) {
					if (abs(it->y - r) > 1) {
						cur = max(cur, it->x + 1);
						break;
					}
				}
			}
			if (c < N - 1) {
				for (auto it = column[c + 1].begin(); it != column[c + 1].end(); ++it) {
					if (abs(it->y - r) > 1) {
						cur = max(cur, it->x + 1);
						break;
					}
				}
			}
			V[r][c] = cur;
			commit.push_back({r,c});
		}

		int ans = 0;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				ans = max(ans, V[i][j]);
//				cout << V[i][j] << ' ';
			}
//			cout << endl;
		}
		cout << ans << endl;
	}
};
