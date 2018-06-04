#include "../../../l/lib.h"
// #include "../l/mod.h"

class ArithmeticSequenceDiv1 {
public:
    int findMinCost(vector <int> x) {
        int ans = 1e9;
        for (int beg = -10000; beg <= -10000; ++beg) {
            for (int dif = -100; dif <= 100; ++dif) {
                int cur = 0;
                for (int i = 0; i < x.size(); ++i) {
                    int k = beg + i*dif;
                    cur += abs(k-x[i]);
                }

                ans = min(ans, cur);
            }
        }

        return ans;
    }


    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        cout << findMinCost(A) << '\n';
    }
};
