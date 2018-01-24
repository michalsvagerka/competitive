#include "../l/lib.h"
#include "../l/mod.h"

class prednasky {
public:
	void solve(istream& cin, ostream& cout) {
		int P, S; cin >> P >> S;
		vector<FieldMod> F = FieldMod::fact(100);
		vector<FieldMod> I = FieldMod::invfact(100);

		vector2<FieldMod> A(P+1, S+1), C(P+1, S+1);
		for (int i = 0; i <= P; ++i) {
			FieldMod X = 1;
			for (int j = 0; j <= S; ++j) {
				A[i][j] = X;
				X *= i*(i+1) / 2;
			}
		}

		for (int i = 0; i <= P; ++i) {
			for (int j = 0; j <= S; ++j) {
				C[i][j] = A[i][j];
				for (int k = 0; k < i; ++k) {
					for (int l = 0; l <= j; ++l) {
						C[i][j] -= C[k][l] * A[i-k-1][j-l] * F[j] * I[j-l] * I[l];
					}
				}
			}
		}

		cout << C[P][S] << endl;
	}
};


