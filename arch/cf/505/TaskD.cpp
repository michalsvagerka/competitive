#include "../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    vector2<bool> G(N, N, false);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            G[i][j] = gcd(A[i],A[j]) != 1;
        }
    }
//    cerr << G;
    vector2<bool> L(N+1, N+1, false), R(N+1, N, false);
    for (int i = 0; i < N; ++i) L[1][i] = R[1][i] = true;
    for (int l = 2; l <= N; ++l) {
        for (int c = 0; c < N; ++c) {
            if (c-l+1 >= 0) {
                for (int d = c-l+1; d < c; ++d) {
//                    cout << "L " << l << ' ' << c << ' ' << l-(c-d) << ' ' <<d << ' ' << c-d << endl;
                    L[l][c] = L[l][c] || (G[c][d] && L[l-(c-d)][d] && R[c-d][d]);
                }
            }
            if (c + l <= N) {
                for (int d = c+1; d < c+l; ++d) {

//                    cerr << "R " << l << ' ' << c << ' ' << l-(d-c) << ' ' <<d << ' ' << d-c << endl;
                    R[l][c] = R[l][c] || (G[c][d] && L[d-c][d] && R[l-(d-c)][d]);
                }
            }
        }
    }

//    cout << L << R;

    for (int i = 0; i < N; ++i) {
        if (L[i+1][i] && R[N-i][i]) {
            cout << "Yes\n";
            return;
        }
    }

    cout << "No\n";
}
};
