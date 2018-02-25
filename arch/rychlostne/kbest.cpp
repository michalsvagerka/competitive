#include "../../l/lib.h"
// #include "../l/mod.h"

class kbest {
public:
    void solve(istream& cin, ostream& cout) {
        int N,K; cin >> N >> K;
        vector<pair<int,pii>> J(N);
        for (int i = 0; i < N; ++i) {
            J[i].x = i+1;
            cin >> J[i].y;
        }

        double ans = bshd(0, 1e8, [&](double d) {
            sort(J.begin(),J.end(),[&](const pair<int,pii>&a, const pair<int,pii>&b) {
                return a.y.x - d * a.y.y > b.y.x - d * b.y.y;
            });

            double tot = 0;
            for (int j = 0; j < K; ++j) {
                tot += J[j].y.x - d * J[j].y.y;
            }
            return tot >= 0;
        });

        sort(J.begin(),J.end(),[&](const pair<int,pii>&a, const pair<int,pii>&b) {
            return a.y.x - ans * a.y.y > b.y.x - ans * b.y.y;
        });

        vector<int> Ans(K);
        for (int j = 0; j < K; ++j) Ans[j] = J[j].x;
        cout << Ans;
    }
};
