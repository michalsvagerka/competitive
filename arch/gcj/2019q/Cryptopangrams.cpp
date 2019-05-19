#include "../l/lib.h"
#include "../l/bigint.h"

class Cryptopangrams {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            Num N; int L;
            cin >> N >> L;
            vector<Num> A(L); cin >> A;
            vector<Num> B(L+1);
            for (int i = 1; i < L; ++i) B[i] = Num::gcd(A[i-1], A[i]);

            for (int i = L-2; i > 0; --i) {
                if (B[i] == A[i-1] && B[i+1] != A[i]) {
                    B[i] /= B[i+1];
                }
            }
            for (int i = 2; i < L; ++i) {
                if (B[i] == A[i-1] && B[i-1] != A[i-2]) {
                    B[i] /= B[i-1];
                }
            }

            B[0] = A[0] / B[1];
            B[L] = A[L-1] / B[L-1];
            map<Num, int> M;
            for (Num&b:B) M[b] = 0;
            int i = 0;
            for (auto&m: M) m.y = i++;

            cout << "Case #" << t+1 << ": ";
            for (int i = 0; i <= L; ++i) cout << char(M[B[i]] + 'A');
            cout << '\n';
        }
    }
};
