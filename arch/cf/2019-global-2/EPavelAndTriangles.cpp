#include "../l/lib.h"

class EPavelAndTriangles {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> A(N); cin >> A;

        ll T = 0, S = 0;
        for (int i = 0; i < N; ++i) {
            ll makeUp = min(S, A[i]/2);
            S -= makeUp;
            A[i] -= 2*makeUp;
            T += makeUp;

            ll equi = A[i] / 3;
            A[i] -= 3*equi;
            T += equi;

            S += A[i];
        }

        cout << T << endl;
    }
};
