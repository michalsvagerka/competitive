#include "../l/lib.h"

class EmptyTheBox {
public:
    double minExpectedPenalty(int D, int T) {
        int pref = 0;
        for (int i = 2*D+1; i <= T; ++i) {
            pref += i;
        }
        if (T > 2*D) T = 2*D;

        vector<vector<int>> Sum(300);

        for (int i = 0; i < (1<<T); ++i) {
            int s = 0;
            for (int j = 0; j < T; ++j) {
                if (i&1<<j) s+= j+1;
            }
            Sum[s].push_back(i);
        }

        vector<double> Ans(1<<T, 10000);
        for (int i = 0; i < (1<<T); ++i) {
            int p = 0;
            for (int j = 0; j < T; ++j) {
                if (i&1<<j) p += j+1;
            }
            double ans = 0;
            for (int k = 2; k <= 2*D; ++k) {
                double prob = min(k-1, 2*D-k+1) / double(D*D);
                double best = p;
                for (int s: Sum[k]) {
                    if ((s&i)==s) {
                        best = min(best, Ans[s^i]);
                    }
                }

                ans += best * prob;
            }
            Ans[i] = ans;
        }
//
        return Ans[(1<<T)-1] + pref;
    }

    void solve(istream& cin, ostream& cout) {
        cout << minExpectedPenalty(2, 3) << '\n';
        cout << minExpectedPenalty(6, 2) << '\n';
        cout << minExpectedPenalty(6, 10) << '\n';
        cout << minExpectedPenalty(4, 10) << '\n';

        cout << minExpectedPenalty(6, 50) << '\n';
        cout << minExpectedPenalty(2, 2) << '\n';
    }
};
