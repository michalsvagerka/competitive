#include "../l/lib.h"
// #include "../l/mod.h"

class sovietbinary {
public:
	void solve(istream& cin, ostream& cout) {
		ll X; cin >> X;
		ll R[2] = {1,0};
		while (X) {
			int dig = X % 2;
			ll V[2] = {0,0};

			for (int j = 0; j < 2; ++j) {
				for (int i = 0; i <= 2; ++i) {
					if ((j + i - dig) % 2 == 0) {
						V[(j + i - dig) / 2] += R[j];
					}
				}
			}

			swap(R, V);
			X /= 2;
		}

		cout << R[0] << endl;
	}
};
