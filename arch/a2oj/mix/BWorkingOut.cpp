#include "../l/lib.h"
// #include "../l/mod.h"

class BWorkingOut {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector2<int> A(N, M); cin >> A;
    vector3<int> D(4, N, M, 0);
    vector<pii> S{{0,0},{0,M-1},{N-1,0},{N-1,M-1}};
    vector<pii> R{{1,1},{1,-1},{-1,1},{-1,-1}};
    for (int i = 0; i < 4; ++i) {
        for (int j = S[i].x; j >= 0 && j < N; j+=R[i].x) {
            for (int k = S[i].y; k >= 0 && k < M; k+=R[i].y) {
                D[i][j][k] += A[j][k];
                if (j+R[i].x >= 0 && j+R[i].x < N) D[i][j+R[i].x][k] = max(D[i][j+R[i].x][k], D[i][j][k]);
                if (k+R[i].y >= 0 && k+R[i].y < M) D[i][j][k+R[i].y] = max(D[i][j][k+R[i].y], D[i][j][k]);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i < N-1; ++i) {
        for (int j = 1; j < M-1; ++j) {
            ans = max(ans, D[0][i-1][j] + D[1][i][j+1] + D[2][i][j-1] + D[3][i+1][j]);
            ans = max(ans, D[0][i][j-1] + D[1][i-1][j] + D[2][i+1][j] + D[3][i][j+1]);
        }
    }
    cout << ans << '\n';
}
};
