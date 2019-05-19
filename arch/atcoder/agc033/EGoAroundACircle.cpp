#include "../l/lib.h"
#include "../l/mod.h"

class EGoAroundACircle {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        string S; cin >> S;

        char c = S[0];
        int d = 1, m = -1, so = 1e9;
        for (int i = 1; i < M; ++i) {
            if (S[i] == c) {
                d++;
            } else {
                if (m == -1) m = d;
                if (d % 2 == 1) so = min(so, d);
                d = 0;
            }
        }

        if (m == -1) {
            vector2<FieldMod> X(N, 2, 0);
            X[0][0] = 1;
            for (int i = 1; i < N; ++i) {
                X[i][0] = X[i - 1][0] + X[i - 1][1];
                X[i][1] = X[i - 1][0];
            }

            vector2<FieldMod> Y(N, 2, 0);
            Y[0][1] = 1;
            for (int i = 1; i < N; ++i) {
                Y[i][0] = Y[i - 1][0] + Y[i - 1][1];
                Y[i][1] = Y[i - 1][0];
            }

            cout << X.back()[0] + X.back()[1] + Y.back()[0] << endl;
            return;
        }

        if (N % 2 == 1) {
            cout << 0 << endl;
            return;
        }

        m = min(m, so);
        // max size of consecutive Rs => m
        int b = min(N/2, m/2 + 1);

        vector<FieldMod> H(N/2, 0);
        FieldMod tot = 1;
        H[0] = 1;
        for (int j = 1; j < N/2; ++j) {
            if (j > b)  tot -= H[j-b-1];
            H[j] = tot;
            tot += H[j];
        }

        FieldMod ans = 0;
        for (int i = 1; i <= b; ++i) {
            ans += i * H[N/2-i];
        }
        cout << 2*ans << endl;
    }
};
