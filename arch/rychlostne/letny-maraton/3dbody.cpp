#include "../../../l/lib.h"
// #include "../l/mod.h"

class threedbody {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> X(N), Y(N), Z(N);
        int h = 2;
        for (int i = 0; i < N; ++i) {
            cin >> X[i] >> Y[i] >> Z[i];
            if (i != 0) {
                X[i] -= X[0];
                Y[i] -= Y[0];
                Z[i] -= Z[0];
            }

            if (i == h) {
                if (X[1]*Y[h] == X[h]*Y[1] && Y[1]*Z[h] == Y[h]*Z[1] && Z[1]*X[h] == Z[h]*X[1]) ++h;
            }

            if (i > h) {
                ll detP = X[1] * Y[h] * Z[i] + X[h] * Y[i] * Z[1] + X[i] * Y[1] * Z[h];
                ll detM = X[i] * Y[h] * Z[1] + X[1] * Y[i] * Z[h] + X[h] * Y[1] * Z[i];
                if (detP != detM) {
                    cout << "nie\n";
                    return;
                }
            }
        }

        cout << "ano\n";
    }
};
