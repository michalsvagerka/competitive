#include "../../../l/lib.h"
// #include "../l/mod.h"

class gogopher {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int A; cin >> A;
            if (A <= 20) {
                vector<pii> Q{{2, 2},
                              {2, 3},
                              {4, 2},
                              {4, 3}};
                for (int i = 0; i < 1000; ++i) {
                    cout << Q[i % 4].x << ' ' << Q[i % 4].y << endl;
                    int x, y;
                    cin >> x >> y;
                    if (x == 0 && y == 0) break;
                }
            } else {
                bool ok = false;
                int q = 0;
                for (int i = 0; i < 67 && !ok; ++i) {
                    vector2<bool> U(3,3,false);
                    int s = 0;
                    while (s < 9) {
                        cout << 2 << ' ' << 3*i+2 << endl;
                        int ar, ac; cin >> ar >> ac;
                        ++q;
                        if (ar == -1 && ac == -1) {
                            return;
                        } else if (ar == 0 && ac == 0) {
                            ++s;
                            ok = true;
                        } else {
                            ar%=3; ac%=3;
                            if (!U[ar][ac]) s++;
                            U[ar][ac] = true;
                        }
                    }
                }
                if (q > 650) cerr << q << endl;
            }
        }
    }
};
