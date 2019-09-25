#include "../l/lib.h"

class CCrazyDiamond {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> P(N); cin >> P;
        for (int &p: P) --p;

        vector<int> I(N);
        for (int i = 0; i < N; ++i) {
            I[P[i]] = i;
        }

        vector<pii> Ans;
        auto swp = [&](int i, int j) {
            swap(P[i],P[j]);
            Ans.push_back({i, j});
            I[P[j]] = j;
            I[P[i]] = i;
        };

        auto fix = [&](int i) {
            while (P[i] != i) {
                int j = I[i];
                if (abs(i - j) >= N/2) {
                    swp(i, j);
                } else if (j >= N/2) {
                    swp(j, 0);
                } else {
                    swp(j, N-1);
                }
            }
        };

        for (int i = 0; i < N/2; ++i) {
            fix(N/2+i);
            fix(N/2-i-1);
        }

        cout << Ans.size() << endl;
        for (auto &ans: Ans) cout << ans.x + 1 << ' ' << ans.y + 1 << endl;
    }
};
