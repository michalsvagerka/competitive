#include "../l/lib.h"
// #include "../l/mod.h"

class zbludena {
public:
    void solve(istream& cin, ostream& cout) {
		int T; cin >> T;
		for (int t = 0; t < T; ++t) {
			string S; cin >> S;
			int x = 0, y = 0, q = 0;
			for (char s: S) {
				switch (s) {
					case 'R':
						x++; break;
					case 'L':
						x--; break;
					case 'U':
						y++; break;
					case 'D':
						y--; break;
					default:
						++q;
				}
			}
			cout << x - q << ' ' << y - q << ' ' << x + q << ' ' << y + q << endl;
		}
    }
};
