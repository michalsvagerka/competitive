#include "../l/lib.h"
// #include "../l/mod.h"

class peciatky {
public:
    void solve(istream& cin, ostream& cout) {
		int T; cin >> T;
		for (int t = 0; t < T; ++t) {
			int r,s,rp,sp; cin >> r >> s >> rp >> sp;
			vector2<bool> F(r,s, false);
			for (int i = 0; i < r; ++i) {
				for (int j = 0; j < s; ++j) {
					char c; cin >> c;
					F[i][j] = c == 'x';
				}
			}
			vector<pii> P;
			int fr=-1,fs=-1;
			for (int i = 0; i < rp; ++i) {
				for (int j = 0; j < sp; ++j) {
					char c; cin >> c;
					if (c == 'x') {
						if (fr==-1) { fr = i; fs = j; }
						P.push_back({i,j});
					}
				}
			}
			bool ok = true;
			for (int i = 0; i < r && ok; ++i) {
				for (int j = 0; j < s && ok; ++j) {
					if (F[i][j]) {
						for (pii &p: P) {
							int R = i + p.x - fr;
							int S = j + p.y - fs;
							if (R >= 0 && R < r && S >= 0 && S < s && F[R][S]) {
								F[R][S] = false;
							} else {
								ok = false;
								break;
							}
						}
					}
				}
			}

			cout << (ok ? "ANO" : "NIE") << endl;
		}
    }
};
