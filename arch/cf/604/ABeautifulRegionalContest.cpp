#include "../l/lib.h"

class ABeautifulRegionalContest {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector<int> P(N); cin >> P;
            int p = P[0], c = 1;
            vector<int> C;
            for (int i = 1; i < N; ++i) {
                if (P[i] == p) {
                    c++;
                } else {
                    C.push_back(c);
                    c = 1;
                    p = P[i];
                }
            }
            C.push_back(c);
            int M = C.size();
            vector<int> Pref(M+1, 0);
            for (int i = 0; i < M; ++i) {
                Pref[i+1] = Pref[i] + C[i];
            }
            vector<int> Ans{0,0,0};
            int half = bsh(0, M, [&](int i) { return Pref[i] <= N/2; });
            for (int i = 1; i <= half-2; ++i) {
                int g = Pref[i];
                int si = bsl(i+1, half-1, [&](int j) { return Pref[j] > 2*g; });
                if (si == -1) continue;
                int s = Pref[si] - Pref[i];
                int b = Pref[half] - Pref[si];
                if (g < s && g < b) {
                    Ans = {g,s,b};
                }
            }
            
            cout << Ans;
        }
    }
};
