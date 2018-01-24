#include "../l/lib.h"
// #include "../l/mod.h"

class jedy {
public:
    void solve(istream& cin, ostream& cout) {
		int J, T; cin >> J >> T;
		vector2<bool> R(T, J);
		vector<bool> S(T);
		bool b;
		for (int i = 0; i < T; ++i) {
			for (int j = 0; j < J; ++j) {
				cin >> b;
				R[i][j] = b;
			}
			cin >> b;
			S[i] = b;
		}


		int ansA = 0, ansB = 0, ansC = J;
		vector<bool> NotThere(J, false), There(J, false);
		for (int t = 0; t < T; ++t) {
			if (!S[t]) {
				for (int j = 0; j < J; ++j) {
					if (R[t][j] && !NotThere[j]) {
						NotThere[j] = true;
						++ansB; --ansC;
					}
				}
			}
		}


		for (int t = 0; t < T; ++t) {
			if (S[t]) {
				int count = 0;
				int id = -1;
				for (int j = 0; j < J; ++j) {
					if (R[t][j] && !NotThere[j]) { count++; id = j; }
				}
				if (count == 0) {
					cout << "Incorrect\n";
					return;
				}
				else if (count == 1 && !There[id]) {
					There[id] = true;
					++ansA; --ansC;
				}
			}
		}

		cout << ansB;
		for (int j = 0; j < J; ++j) {
			if (NotThere[j]) cout << ' ' << j;
		}
		cout << endl;

		cout << ansA;
		for (int j = 0; j < J; ++j) {
			if (There[j]) cout << ' ' << j;
		}
		cout << endl;

		cout << ansC;
		for (int j = 0; j < J; ++j) {
			if (!There[j] && !NotThere[j]) cout << ' ' << j;
		}
		cout << endl;

	}
};
