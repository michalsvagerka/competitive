#include "../l/lib.h"
// #include "../l/mod.h"

class A {
public:

    void solve(istream& cin, ostream& cout) {
		int R,C; cin >> R >> C;
		stringstream ss;
		for (int i = 0; i < C; ++i) ss << '.';
		vector<string> A(R, ss.str());
		int t = 7;
		for (int r = 0; r < R; r+=3) {
			for (int c = 0; c < C; c+=3) {
				if (t) {
					A[r][c] = 'T';
					--t;
				}
			}
		}
		if (t) cout << "impossible\n";
		else {
			for (string &s: A) cout << s << endl;
		}
    }
};
