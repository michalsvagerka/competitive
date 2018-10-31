#include "../l/lib.h"
 #include "../l/mod.h"

class D {
public:
void solve(istream& cin, ostream& cout) {
    int N, K; cin >> N >> K;
    vector<int> C(2*N, -1);
    for (int i = 0; i < K; ++i) {
        int A,B; cin >> A >> B;
        --A; --B;
        C[A] = B;
        C[B] = A;
    }

    vector<FieldMod> Pair(N+1, 1);
    for (int i = 2; i <= N; ++i) Pair[i] = Pair[i-1] * (2*i-1);
    int R = N-K;

    vector2<FieldMod> Any(4*N, N+1, 0);
    vector2<FieldMod> Single(4*N, N+1, 0);
    for (int i = 0; i < 2*N; ++i) {
        for (int c = 1; i + 2*c < 2*N; ++c) {
            int j = (i + 2*c) % (2*N);

            bool out = false;
            int unused = 0;
            for (int k = i; k < i+2*c; ++k) {
                if (C[k] == -1) unused++;
                else if (C[k] < i || C[k] >= j) out = true;
            }

            if (!out) {
                Any[2*N+i][c] = Any[i][c] = Pair[unused/2];
                Any[2*N+i+2*c][N-c] = Any[i+2*c][N-c] = Pair[R-unused/2];
            }
        }
    }

    for (int c = 1; c < N; c++) {
        for (int i = 0; i < 2*N; ++i) {
            int j = (i+2*c-1)%(2*N);
            Single[i][c] = Any[i][c];
            for (int k = 1; k < c; ++k) {
                Single[i][c] -= Single[i][k] * Any[i + 2*k][c - k];
            }
            Single[2 * N + i][c] = Single[i][c];
        }
    }

    Any[0][N] = Pair[R];
    Single[0][N] = Pair[R];
    for (int i = 0; i < 2*N; ++i) {
        vector<FieldMod> cur(N+1, 0);
        for (int c = 1; c < N; ++c) cur[c] = Single[i][c];
        for (int j = 1; j + i/2 < N; j++) {
            for (int k = 1; k + j + i/2 < N; ++k) {
                cur[j+k] += cur[j] * Single[2*j+i][k];
            }

            if (j != 0) Single[0][N] -= cur[j] * Single[2*j+i][N-j];
        }
    }

    FieldMod ans = Single[0][N];
    cout << ans << endl;
    for (int i = 0; i < 2*N; ++i) {
        vector<FieldMod> cur(N+1, 0);
        for (int c = 1; c < N; c++) cur[c] = Single[i][c];
        for (int j = 1; j < N; j++) {
            for (int c = 1; c+j <= N; c++) {
                cur[j+c] += cur[j] * Single[2*j+i][c];
            }
        }

        ans += cur[N];
    }

    cout << ans << endl;
}
};
