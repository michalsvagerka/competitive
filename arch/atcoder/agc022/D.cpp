#include "../../../l/lib.h"
// #include "../l/mod.h"

class D {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        ll L; cin >> L; L *= 2;
        vector<int> X(N), T(N); cin >> X >> T;
        vector2<ll> S(N, 3);
        for (int i = 0; i < N; ++i) {
            ll s = L+T[i]-1;
            S[i][0] = s / L; // just passing through
            S[i][1] = (s + 2*X[i]) / L - 1; // coming from left, going left
            S[i][2] = (L + s - 2*X[i]) / L; // coming from right, going right
        }

        if (N == 1) {
            cout << (1+S[0][1])*L << endl;
            return;
        }

        ll inf = 1e16;
        vector<ll> D{1};
        for (int i = 0; i < N-1; ++i) {
            vector<ll> E(min(N/2,int(D.size())+1), inf);
            for (int j = 0; j < D.size(); ++j) {
                if (j > 0) E[j-1] = min(E[j-1], D[j] + S[i][1]);
                if (j+1 < E.size()) E[j+1] = min(E[j+1], D[j] + S[i][2]);
                E[j] = min(E[j], D[j] + S[i][0]);
            }
            swap(D,E);
        }

        cout << (D[0]+S[N-1][1])*L << endl;
    }
};
