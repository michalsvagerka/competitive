#include "../../../l/lib.h"
 #include "../../../l/primes.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    auto W = Sieve{55}.primes();

    vector<int> P(59, 0);
    for (int i = 1; i < 59; ++i) {
        for (int w = 0; w < W.size(); ++w) {
            if (i % W[w] == 0) {
                P[i] |= (1<<w);
            }
        }
    }

    int infty = 1e9;
    vector2<pii> D(N+1, 1<<W.size(), {infty, -1});
    D[0][0] = {0, -1};
    for (int i = 0; i < N; ++i) {
        for (int m = 0; m < (1<<W.size()); ++m) {
            if (D[i][m].x == infty) continue;
            for (int z = 1; z < 59; ++z) {
                if ((m & P[z]) == 0) {
                    D[i+1][m|P[z]] = min(D[i+1][m|P[z]], {D[i][m].x + abs(A[i] - z), z});
                }
            }
        }
    }

    pii lo{infty, 0};
    for (int m = 0; m < (1<<W.size()); ++m) {
        lo = min(lo, {D[N][m].x, m});
    }

    vector<int> B(N);
    int m = lo.y;
    for (int i = N; i > 0; --i) {
        B[i-1] = D[i][m].y;
        m ^= P[D[i][m].y];
    }
    cout << B;
};
};
