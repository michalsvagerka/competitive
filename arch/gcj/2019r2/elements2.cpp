#include "../l/lib.h"
#include "../l/frac.h"

class elements2 {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector<pii> A(N); cin >> A;

            Fraction lo {-1000000000, 1};
            Fraction hi {1000000000, 1};
            for (int i = 0; i < N; ++i) {
                for (int j = i+1; j < N; ++j) {
                    if (A[i].x != A[j].x && A[i].y != A[j].y) {
                        int dx = A[i].x - A[j].x;
                        int dy = A[j].y - A[i].y;
                        if (dx < 0 && dy > 0) continue;
                        if (dx > 0 && dy < 0) continue;

                        Fraction F{dx, dy};
                        if (dy < 0) {
                            if (F < hi) hi = F;
                        } else {
                            if (F > lo) lo = F;
                        }
                    }
                }
            }

            bool possible = false;

            ll x, y;
            if (lo < hi) {
                for (x = 1; x < 1000; ++x) {
                    ll a = max(1LL, (lo.u * x) / lo.v + 1);
                    ll b = (hi.u * x - 1) / hi.v;
                    if (a <= b) {
                        y = a;
                        possible = true;
                        vector<ll> B(N);
                        for (int i = 0; i < N; ++i) {
                            B[i] = x * A[i].x + y * A[i].y;
                        }

                        for (int i = 0; i < N-1; ++i) {
                            possible &= B[i] < B[i+1];
                        }
                        break;
                    }
                }
                
                
//                x = bsl(1LL, 2000000000LL, [&](ll C) {
//                    ll a = max(1LL, (lo.u * C) / lo.v + 1);
//                    ll b = (hi.u * C - 1) / hi.v;
//                    return a <= b;
//                });
//
//                if (x != -1) {
//                    y = max(1LL, (lo.u * x) / lo.v + 1);
//
//                    vector<ll> B(N);
//                    for (int i = 0; i < N; ++i) {
//                        B[i] = x * A[i].x + y * A[i].y;
//                    }
//
//                    possible = true;
//                    for (int i = 0; i < N-1; ++i) {
//                        possible &= B[i] < B[i+1];
//                    }
//                }
            }

            cout << "Case #" << t+1 << ": ";
            if (possible) {
                cout << x << ' ' << y;
            } else {
                cout << "IMPOSSIBLE";
            }

            cout << endl;
        }

    }
};
