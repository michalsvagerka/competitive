#include "../l/lib.h"

class JoinTheRanks {
public:

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int R, S; cin >> R >> S;
            vector<pii> Ans;
            if (Ans.empty()) {
                vector<int> A;
                for (int i = 0; i < S; ++i) {
                    for (int j = 0; j < R; ++j) {
                        A.push_back(j);
                    }
                }

                while (true) {
                    int t = R*S-1;
                    while (A[t] == A[R*S-1]) --t;
                    ++t;
                    int s = t-1;
                    while (s >= 0 && A[s] == A[t-1]) --s;
                    ++s;

                    if (s == 0) break;
                    // move [s,R*S) somewhere (maybe)

                    int u = s-1;
                    while (u >= 0 && (A[u] != A[s] || A[u+1] != A[t])) --u;

                    if (u == -1) {
                        if (A[t] == 0) Ans.push_back({R*S-t, t});
                        break;
                    } else {
                        Ans.push_back({R*S-s, s-u-1});

                        pii ans = Ans.back();
                        vector<int> B;
                        int a = R*S-ans.x-ans.y;
                        for (int i = 0; i < a; ++i) B.push_back(A[i]);
                        for (int i = a + ans.y; i < R*S; ++i) B.push_back(A[i]);
                        for (int i = a; i < a + ans.y; ++i) B.push_back(A[i]);
                        swap(A,B);
                    }
                }
            }


            cout << "Case #" << t+1 << ": " << Ans.size() << '\n';
            for (pii ans: Ans) cout << ans << '\n';
        }
    }
};
