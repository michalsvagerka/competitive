#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N, M, Q; cin >> N >> M >> Q;
    vector2<pii> A(N, M);
    vector2<int> B(N, M, 0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            A[i][j] = {i,j};
        }
    }

    for (int q = 0; q < Q; ++q) {
        int t; cin >> t;
        if (t == 1) {
            int r; cin >> r; --r;
            rotate(A[r].begin(),A[r].begin()+1,A[r].end());
        } else if (t == 2) {
            int c; cin >> c; --c;
            pii top = A[0][c];
            for (int r = 0; r < N-1; ++r) A[r][c] = A[r+1][c];
            A[N-1][c] = top;
        } else {
            int r, c, v; cin >> r >> c >> v;
            --r; --c;
            pii q = A[r][c];
            B[q.x][q.y] = v;
        }
    }
    for (auto&b:B) cout << b;
}
};
