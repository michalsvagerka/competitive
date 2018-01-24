#include "../l/lib.h"
// #include "../l/mod.h"

class brak {
public:
	void solve(istream& cin, ostream& cout) {
		int T; cin >> T;
		for (int t = 0; t < T; ++t) {
			int R,S; cin >> R >> S;
			vector2<char> F(R,S);

			vector<pair<int, pii>> H;
			vector2<int> D(R,S,-1);
			int sr,ss;
			for (int r = 0; r < R; ++r) {
				for (int s = 0; s < S; ++s) {
					cin >> F[r][s];
					if (F[r][s] == '*') {  H.push_back({0, {r,s}}); }
					if (F[r][s] == 'S') { sr = r; ss = s; }
				}
			}

			int i = 0;
			while (i < H.size()) {
				auto x = H[i++];
				int r = x.y.x, s = x.y.y, v = x.x;
				if (D[r][s] != -1) continue;
				D[r][s] = v;
				if (F[r][s] == 'S') break;
				if (r>0 && F[r-1][s] != 'X') H.push_back({v+1, {r-1,s}});
				if (r<R-1 && F[r+1][s] != 'X') H.push_back({v+1, {r+1,s}});
				if (s>0 && F[r][s-1] != 'X') H.push_back({v+1, {r,s-1}});
				if (s<S-1 && F[r][s+1] != 'X') H.push_back({v+1, {r,s+1}});
			}

			if (D[sr][ss] == -1) { cout << "BRAK\n"; continue; }
			stringstream A;
			while (F[sr][ss] != '*') {
				int v = D[sr][ss];
				if (sr < R-1 && D[sr+1][ss] == v-1) { sr += 1; A << 'D'; }
				else if (sr > 0 && D[sr-1][ss] == v-1) { sr -= 1; A << 'G'; }
				else if (ss > 0 && D[sr][ss-1] == v-1) { ss -= 1; A << 'L'; }
				else if (ss < S-1 && D[sr][ss+1] == v-1) { ss += 1; A << 'P'; }
				else { break; }
			}
			cout << A.str() << '\n';
		}
	}
};
