#include "../../../l/lib.h"

class FCardsAndJoy {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> C(N*K); cin >> C;
        vector<int> F(N); cin >> F;
        vector<int> H(K); cin >> H;
        vector<int> D(100001, 0), FF(100001, 0);
        for (int c: C) D[c]++;
        for (int f: F) FF[f]++;
        ll ans = 0;
        for (int i = 0; i <= 100000; ++i) {
            int A = FF[i], B = D[i];
            vector2<int> E(A+1, B+1, -1000000000);
            E[0][0] = 0;
            for (int a = 0; a < A; ++a) {
                for (int b = 0; b <= B; ++b) {
                    for (int c = 0; c <= K; ++c) {
                        if (b + c <= B) {
                            E[a+1][b+c] = max(E[a+1][b+c], E[a][b] + (c>0?H[c-1]:0));
                        }
                    }
                }
            }
            ans += *max_element(E[A].begin(),E[A].end());
        }
        cout << ans << '\n';
    }
};
