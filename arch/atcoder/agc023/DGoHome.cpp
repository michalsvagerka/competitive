#include "../l/lib.h"

class DGoHome {
public:
    void solve(istream& cin, ostream& cout) {
        int N, S; cin >> N >> S;
        vector<ll> X(N), P(N);
        for (int i = 0; i < N; ++i) {
            cin >> X[i] >> P[i];
            X[i] -= S;
        }

        int l = 0, r = N-1;
        while (X[l] < 0 && X[r] > 0) {
            if (P[l] < P[r]) {
                X[r] *= 2;
                X[r] -= X[l];
                while (X[l] < 0 && P[l] < P[r]) {
                    P[r] += P[l];
                    P[l] = 0;
                    ++l;
                }
            } else if (P[l] >= P[r]) {
                X[l] *= 2;
                X[l] -= X[r];
                while (X[r] > 0 && P[l] >= P[r]) {
                    P[l] += P[r];
                    P[r] = 0;
                    --r;
                }
            }
        }

        cout << max(-X[l], X[r]) << endl;
    }
};
