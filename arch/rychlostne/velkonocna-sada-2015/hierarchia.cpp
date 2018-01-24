#include "../l/lib.h"
// #include "../l/mod.h"

class hierarchia {
public:
    void solve(istream& cin, ostream& cout) {
		int N;
		cin >> N;
		vector<int> A(N); cin >> A;
		multiset<int> S;
		S.insert(0);
		for (int a: A) {
			auto it = S.lower_bound(a);
			if (it == S.begin()) {
				cout << "NO\n";
				return;
			}

			--it;
			S.erase(it);
			S.insert(a);
			S.insert(a);
		}
		cout << "YES\n";
    }
};
