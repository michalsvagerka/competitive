#include "../l/lib.h"

class AFeedingChicken {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int R, C, K; cin >> R >> C >> K;
            vector<string> F(R); cin >> F;
            int f = 0;
            for (int i = 0; i < R; ++i) {
                f += count(F[i].begin(),F[i].end(),'R');
            }
            vector<string> Ans(R, string(C, '_'));
            int r = 0, c = 0;
            for (int i = 0; i < K; ++i) {
                int q = f/K + (i<f%K) + (i==K-1);
                while (q > 0 && r < R) {
                    if (i < 10) Ans[r][c] = char('0'+i);
                    else if (i < 36) Ans[r][c] = char('a'+i-10);
                    else Ans[r][c] = char('A'+i-36);
                    if (F[r][c] == 'R') --q;
                    if (r%2==0) {
                        c++;
                        if (c == C) {
                            c = C-1;
                            r++;
                        }
                    } else {
                        c--;
                        if (c == -1) {
                            c = 0;
                            r++;
                        }
                    }
                }
            }
            for (string ans: Ans) cout << ans << '\n';
        }
    }
};
