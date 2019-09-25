#include "../l/lib.h"

constexpr int INFTY = 1e6;

class Grading {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 1; t <= T; ++t) {
            int H, S, K; cin >> H >> S >> K;
            vector<string> P(H); cin >> P;
            vector<int> Q(K); cin >> Q;
            vector<int> Ans(S*H+30, 100000); // deletions => min no of switches

            for (int a = 0; a < 2; ++a) {
                vector<int> DP(H+30, 0);
                for (int j = 0; j < S; ++j) {
                    char c = "AB"[a];
                    int k = 0;
                    vector<int> G;
                    while (k < H) {
                        int w = 0;
                        while (k + w < H && P[k+w][j] == c) ++w;
                        G.push_back(w);
                        k += w;
                        c = "AB"[c=='A'];
                    }

                    int M = G.size();
                    vector2<int> R(M+30, M+30, INFTY); // groups processed x context switches -> min deletions
                    R[1][0] = 0;
                    for (int i = 1; i < M; ++i) {
                        for (int j = 0; j <= M; ++j) {
                            if (R[i][j] == INFTY) continue;
                            R[i+1][j+1] = min(R[i+1][j+1], R[i][j]); // just process normally
                            R[i+2][j] = min(R[i+2][j], R[i][j] + G[i]); // lose the papers and process the next batch normally
                        }
                    }

                    vector<int> W(H+30, INFTY);
                    for (int i = 0; i <= M+1; ++i) W[i] = min(R[M][i], R[M+1][i]); // M or M+1 batches are processed => all done
                    for (int i = 0; i <= H; ++i) W[i+1] = min(W[i+1], W[i]); // more switches => no more deletions
                    for (int i = 0; i <= H+1; ++i) DP[i] += W[i]; // combine with other stacks
                }

                // min DP[i] deletions for i switches => max no of switches for DP[i] deletes is i
                for (int i = 0; i <= H+1; ++i) Ans[DP[i]] = min(Ans[DP[i]], i);
            }

            // more deletions => no more switches
            for (int i = 0; i <= S*H; ++i) Ans[i+1] = min(Ans[i+1], Ans[i]);
            vector<int> PT(K);
            for (int i = 0; i < K; ++i) PT[i] = Ans[Q[i]] + 1;
            cout << "Case #" << t << ": " << PT;
        }
    }
};
