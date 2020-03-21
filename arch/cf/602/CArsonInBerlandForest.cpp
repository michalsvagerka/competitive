#include "../l/lib.h"

class CArsonInBerlandForest {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<string> A(N); cin >> A;

        vector<pii> Q;
        vector2<int> D(N, M, 1000006);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (A[i][j] == '.') {
                    D[i][j] = 0;
                    continue;
                }
                bool one = false;
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        int a = i+di;
                        int b = j+dj;
                        one |= a<0||a>=N||b<0||b>=M||A[a][b]=='.';
                    }
                }
                if (one) {
                    D[i][j] = 1;
                    Q.push_back({i,j});
                }
            }
        }

        for (int q = 0; q < Q.size(); ++q) {
            int i = Q[q].x, j = Q[q].y;
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    int a = i+di;
                    int b = j+dj;
                    if (a<0||a>=N||b<0||b>=M) continue;
                    if (D[a][b] != 1000006) continue;
                    D[a][b] = D[i][j]+1;
                    Q.push_back({a,b});
                }
            }
        }

        vector2<int> S(N+1, M+1, 0);
        int mx = bsh(1, N*M, [&](int q) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    S[i+1][j+1] = S[i][j+1] + S[i+1][j] - S[i][j] + (D[i][j] >= q);
                }
            }
            
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    int a = max(0,i-q+1);
                    int b = max(0,j-q+1);
                    int c = min(i+q-1,N-1);
                    int d = min(j+q-1,M-1);
                    int tot = S[c+1][d+1] - S[c+1][b] - S[a][d+1] + S[a][b];
                    if ((tot == 0) != (A[i][j] == '.')) return false;
                }
            }
            return true;
        });

        vector<string> Ans(N, string(M, ' '));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                Ans[i][j] = ".X"[D[i][j] >= mx];
            }
        }
        cout << mx-1 << endl;
        for (string&ans: Ans) cout << ans << '\n';
    }
};
