#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        for (int i = 0; i < N; ++i) {
            ll P,Q,B; cin >> P >> Q >> B;
            ll G = P == 0 ? 1 : gcd(P,Q);
            P /= G;
            Q /= G;
            P %= Q;
            if (P == 0) {
                cout << "Finite\n";
            } else {
                G = B;
                do {
                    G = gcd(Q, G);
                    while (G != 1 && Q % G == 0) Q /= G;
                } while (G != 1);

                if (Q == 1) {
                    cout << "Finite\n";
                } else {
                    cout << "Infinite\n";
                }
            }
        }
    }
};
