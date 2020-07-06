#include "../l/lib.h"

constexpr int BIT = 62;

class AXorBattle {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector<ll> A(N); cin >> A;
            string S; cin >> S;
            vector<ll> B(BIT, 0);
            bool fail = false;
            for (int i = N-1; i >= 0; --i) {
                if (S[i] == '0') {
                    ll a = A[i];
                    for (int b = BIT-1; b >= 0; --b) {
                        if (a&1LL<<b) {
                            if (B[b] != 0) {
                                a ^= B[b];
                            } else {
                                B[b] = a;
                                break;
                            }
                        }
                    }
                } else {
                    ll a = A[i];
                    for (int b = BIT-1; b >= 0; --b) {
                        if (a&1LL<<b) {
                            if (B[b] != 0) {
                                a ^= B[b];
                            } else {
                                fail = true;
                                break;
                            }
                        }
                    }
                }
            }
            cout << (fail?'1':'0') << '\n';
        }
    }
};
