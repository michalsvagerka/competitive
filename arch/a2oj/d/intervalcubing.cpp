#include "../../../l/lib.h"
 #include "../../../l/mod.h"

typedef Field<95542721> F;

class intervalcubing {
public:
    vector2<F> D;
    vector<int> S;
    int M;

    F sum(int I, int L, int R, int l, int r) {
        if (l <= L && r >= R) return D[I][S[I]];
        if (l >= R || r <= L) return 0;
        if (S[I]) {
            rotate(D[I].begin(), D[I].begin() + S[I], D[I].end());
            (S[2 * I] += S[I]) %= 48;
            (S[2 * I + 1] += S[I]) %= 48;
            S[I] = 0;
        }
        return sum(2*I, L, (L+R)/2, l, r) + sum(2*I+1, (L+R)/2, R, l, r);
    }

    void update(int I, int L, int R, int l, int r) {
        if (l <= L && r >= R) { (++S[I]) %= 48; return; }
        else if (l >= R || r <= L) return;
        if (S[I]) {
            (S[2 * I] += S[I]) %= 48;
            (S[2 * I + 1] += S[I]) %= 48;
            S[I] = 0;
        }
        update(2*I, L, (L+R)/2, l, r);
        update(2*I+1, (L+R)/2, R, l, r);
        for (int i = 0; i < 48; ++i) {
            D[I][i] = D[2*I][(i+S[2*I])%48] + D[2*I+1][(i+S[2*I+1])%48];
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        M = 1<<logceil(N);
        D = vector2<F>(2*M, 48, 0);
        S = vector<int>(2*M, 0);

        for (int i = 0; i < N; ++i) {
            D[i+M][0] = A[i]%95542721;
            for (int j = 1; j < 48; ++j) D[i+M][j] = D[i+M][j-1]*D[i+M][j-1]*D[i+M][j-1];
        }

        for (int i = M-1; i > 0; --i) {
            for (int j = 0; j < 48; ++j) {
                D[i][j] = D[2*i][j] + D[2*i+1][j];
            }
        }

        int Q; cin >> Q;
        for (int q = 0; q < Q; ++q) {
            int t,l,r; cin >> t >> l >> r;
            --l;
            if (t == 1) {
                cout << sum(1, 0, M, l, r) << '\n';
            } else {
                update(1, 0, M, l, r);
            }
        }



    }
};
