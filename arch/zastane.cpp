#include "../l/lib.h"
// #include "../l/mod.h"

class zastane {
public:
    void solve(istream& cin, ostream& cout) {
		ll N; cin >> N;
		while (N % 2 == 0) N /= 2;
		if (N == 1) cout << "ANO"; else cout << "NIE";
		cout << endl;
    }
};
