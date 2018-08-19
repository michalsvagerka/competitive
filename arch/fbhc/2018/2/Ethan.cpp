#include "../l/lib.h"
// #include "../l/mod.h"

class Ethan {
public:
void solve(istream& cin, ostream& cout) {
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        cout << "Case #" << t+1 << ": ";
        int N, K; cin >> N >> K;
        if (N == 2 || K <= 3) {
            cout << "0\n1\n";
        } else if (K >= N) {
            cout << (2*K - N) * (N-1) / 2 - K << '\n';
            cout << N << '\n';
            for (int i = 1; i < N; ++i) {
                cout << i << ' ' << i + 1 << ' ' << K - i << '\n';
            }
        } else {
            cout << K * (K-1) / 2 - K << '\n';
            cout << K << '\n';
            for (int i = 1; i < K; ++i) {
                cout << i << ' ' << (i==K-1?N:i+1) << ' ' << K - i << '\n';
            }
        }
        cout << "1 " << N << ' ' << K << '\n';
    }
}
};
