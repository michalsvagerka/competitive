#include "../../../l/lib.h"
// #include "../l/mod.h"

class sortfiles {
public:
    int N;
    vector<int> A;
    vector<vector<int>> Q;
    map<vector<int>, int> R;
    vector<vector<int>> Z;

    int cost(int d) {
        if (Z[d].size() == 1) return 0;
        auto it = R.find(Z[d]);
        if (it != R.end()) return it->y;
        int n = d - d%2 + 2;
        int ans = 1e9;
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                if (A[i] * A[j] >= ans) continue;

                Z[n].clear();
                Z[n+1].clear();
                for (int p:Z[d]) {
                    if (Q[p][i] < Q[p][j]) {
                        Z[n].push_back(p);
                    } else {
                        Z[n+1].push_back(p);
                    }
                }

                if (!Z[n].empty() && !Z[n+1].empty()) {
                    ans = min(ans, A[i] * A[j] + max(cost(n), cost(n+1)));
                }
            }
        }
        return R[Z[d]] = ans;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        A.resize(N);
        cin >> A;
        sort(A.begin(),A.end());

        Z.resize(50);

        vector<int> P(N);
        for (int i = 0; i < N; ++i) P[i] = i;
        do {
            Q.push_back(P);
            Z[0].push_back(Z[0].size());
        } while (next_permutation(P.begin(),P.end()));

        cout << cost(0) << endl;
    }
};
