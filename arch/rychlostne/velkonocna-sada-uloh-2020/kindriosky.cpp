#include "../l/lib.h"

class kindriosky {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        ll ans = 0;
        int N = S.size();
        vector<int> C(N+2, -1), D(N+2, -1);
        map<int, vector<int>> W;
        W[0].push_back(0);
        C[0] = 0; D[0] = 0;
        int L = 1, Q = 0;
        string T;
        for (char s: S) {
            if (s == '(') {
                Q++;
                C[L] = 0;
                D[L] = Q;
                W[Q].push_back(L);
                L++;
                T.push_back(s);
            } else if (s == ')') {
                Q--;
                if (!W[Q].empty()) {
                    if (W[Q-1].empty() || W[Q-1].back() < W[Q].back()) {
                        C[L] = C[W[Q].back()]+1;
                    } else {
                        C[L] = 0;
                    }
                } else {
                    C[L] = 0;
                }
                D[L] = Q;
                W[Q].push_back(L);
                ans += C[L];
                L++;
                T.push_back(s);
            } else {
                if (T.back() == '(') {
                    T.pop_back();
                    --L;
                    W[Q].pop_back();
                    D[L] = -1;
                    C[L] = -1;
                    Q--;
                } else {
                    T.pop_back();
                    --L;
                    ans -= C[L];
                    W[Q].pop_back();
                    D[L] = -1;
                    C[L] = -1;
                    Q++;
                }
            }
            cout << ans << '\n';
        }
    }
};
