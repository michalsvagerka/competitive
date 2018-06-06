#include "../l/lib.h"
// #include "../l/mod.h"

class bitsofmerryengland {
public:
    void solve(istream& cin, ostream& cout) {
        int N,M; cin >> N >> M;
        vector<int> A(N), R(M, 0), F(M, N);
        cin >> A;

        for (int i = 0; i < N; ++i) {
            int k = -1;
            for (int j = 0; j < M; ++j) {
                if (R[j] == A[i]) {
                    k = j;
                    break;
                }
            }

            if (k == -1) {
                pii l = {F[0], 0};
                for (int j = 0; j < M; ++j) l = max(l, {F[j],j});
                k = l.y;
                cout << char('a'+k) << '=' << A[i] << '\n';
                R[k] = A[i];
                F[k] = N;
                for (int j = N-1; j > i; --j) if (A[j] == A[i]) F[k] = j;
            }

            cout << "print(" << char('a'+k) << ")\n";
        }

    }
};
