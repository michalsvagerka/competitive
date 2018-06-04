#include "../../../l/lib.h"
// #include "../l/mod.h"

class cliqueproblem {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> X(N);
        for (int i = 0; i < N; ++i) {
            cin >> X[i].x >> X[i].y;
        }
        sort(X.begin(),X.end());

        vector<int> S{-2000000000};
        for (int i = 0; i < N; ++i) {
            int t = bsh(0, int(S.size())-1, [&](int k) { return X[i].x-X[i].y >= S[k]; });
            if (t == S.size()-1) {
                S.push_back(X[i].x+X[i].y);
            } else {
                S[t+1] = min(S[t+1], X[i].x+X[i].y);
            }
        }

        cout << S.size()-1 << '\n';
    }
};
