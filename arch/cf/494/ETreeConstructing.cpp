#include "../../../l/lib.h"

class ETreeConstructing {
public:
    int N, D, K;
    vector<pii> E;

    void put(int u, int d, int h) {
        if (h == 0) return;

        for (int i = 0; i < d; ++i) {
            if (E.size() < N-1) {
                int v = E.size()+2;
                E.emplace_back(u, v);
                put(v, K-1, h-1);
            } else break;
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> D >> K;
        if (D >= N) {
            cout << "NO\n";
            return;
        }
        if (K == 1) {
            if (N == 1) {
                cout << "NO\n";
            } else if (N == 2) {
                cout << "YES\n1 2\n";
            } else {
                cout << "NO\n";
            }
            return;
        }

        for (int i = 0; i < D; ++i) {
            E.emplace_back(i+1, i+2);
        }

        if (K > 2) {
            for (int i = 2; i <= D; ++i) {
                put(i, K - 2, min(i - 1, D + 1 - i));
            }
        }

        if (E.size() < N-1) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            for (pii e: E) cout << e << '\n';
        }
    }
};
