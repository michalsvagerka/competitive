#include "../l/lib.h"
// #include "../l/mod.h"

class hranaruby {
public:
    void solve(istream& cin, ostream& cout) {
		int B; cin >> B;
		int C = B / 320;
		int R = B % 320;

		cout << (2*(C + (R != 0)) + 1) << '\n';
		for (int i = 0; i < C; ++i) {
			cout << (i+1) << ' ' << (i+321) << ' ';
		}
		if (R != 0) {
			cout << 641 << ' ' << 641 + R << ' ';
		}
		cout << "0\n";
    }
};
