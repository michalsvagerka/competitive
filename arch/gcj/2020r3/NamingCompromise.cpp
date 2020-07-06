#include "../l/lib.h"

class NamingCompromise {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            string S, T; cin >> S >> T;
            int N = S.size(), M = T.size();
            reverse(S.begin(),S.end());
            reverse(T.begin(),T.end());
            vector2<int> D(N+1, M+1, N+M+2);
            D[0][0] = 0;
            for (int i = 0; i <= N; ++i) {
                for (int j = 0; j <= M; ++j) {
                    if (i < N && j < M && S[i] == T[j]) D[i+1][j+1] = min(D[i+1][j+1], D[i][j]);
                    if (i < N && j < M) D[i+1][j+1] = min(D[i+1][j+1], D[i][j]+1);
                    if (i < N) D[i+1][j] = min(D[i+1][j], D[i][j]+1);
                    if (j < M) D[i][j+1] = min(D[i][j+1], D[i][j]+1);
                }
            }

            string Ans;
            int i = N, j = M;
            bool takeS = true;
            while (i > 0 || j > 0) {
                if (i > 0 && j > 0 && S[i-1] == T[j-1] && D[i][j] == D[i-1][j-1]) {
                    Ans.push_back(S[i-1]);
                    --i;
                    --j;
                } else if (i > 0 && j > 0 && D[i][j] == D[i-1][j-1] + 1) {
                    Ans.push_back(takeS ? S[i-1] : T[j-1]);
                    takeS = !takeS;
                    --i;
                    --j;
                } else if (i > 0 && D[i][j] == D[i-1][j] + 1) {
                    if (takeS) Ans.push_back(S[i-1]);
                    takeS = !takeS;
                    --i;
                } else {
                    if (!takeS) Ans.push_back(T[j-1]);
                    takeS = !takeS;
                    --j;
                }
            }

            cout << "Case #" << t+1 << ": " << Ans << endl;
        }
    }
};
