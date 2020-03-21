#include "../l/lib.h"
#include "../l/nsegtree.h"

constexpr int MAX = 2048;
constexpr int MASK = 2047;
constexpr int LEN = 11;
constexpr int INF = -1e9;

class DRealityShow {
public:
    inline void mx(int&a, int b) { a = max(a, b); }

    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> L(N), S(N), C(N+M); cin >> L >> S >> C;
        for (int &l: L) --l;

        vector<int> PC(N+M+LEN+2, 0);
        for (int i = 0; i < N+M; ++i) PC[i+1] = PC[i] + C[i];
        for (int i = N+M; i < N+M+LEN+1; ++i) PC[i+1] = PC[i];

        vector2<int> D(M + LEN + 1, MAX, INF);
        for (int i = 0; i < M; ++i) D[i][0] = 0;
        for (int i = N-1; i >= 0; --i) {
            int my = C[L[i]] - S[i];
            int m = 0;
            while (D[L[i]][m] != INF) ++m;
            for (int b = m-1; b >= 0; --b) {
                mx(D[L[i]][b+1], D[L[i]][b] + my + PC[L[i]+1+__builtin_ctz(~b)] - PC[L[i]+1]);
            }

            for (int b = 0; b <= m; ++b) {
                for (int j = 1; j <= LEN; ++j) {
                    mx(D[L[i]+j][b>>j], D[L[i]][b]);
                }
            }

            for (int j = L[i]+LEN+1; j < M+LEN; ++j) mx(D[j][0], D[j-1][0]);
        }
        int ans = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < MAX; ++j) {
                mx(ans, D[i][j]);
            }
        }
        cout << ans << '\n';
    }
};
