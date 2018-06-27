#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:

    vector<vector<int>> P;

    bool backtrack(int i) {
        if (i == 200) return true;

        for (int dx : {-1, 1}) {
            vector<int> Z(i+3, 0);
            for (int j = 0; j < i+2; ++j) {
                Z[j+1] = P[i+1][j];
            }

            for (int j = 0; j < i+1; ++j) {
                Z[j] += dx * P[i][j];
            }

            bool ok = true;
            for (int j = 0; j < i+3; ++j) ok &= abs(Z[j]) <= 1;
            if (ok) {
                P.push_back(Z);
                if (backtrack(i+1)) return true;
                P.pop_back();
            }
        }
        return false;
    }

    void solve(istream& cin, ostream& cout) {
        P.push_back({1});
        P.push_back({0, 1});
        backtrack(0);
        int N; cin >> N;
        cout << P[N].size()-1 << '\n' << P[N] << P[N-1].size()-1 << '\n' << P[N-1];
    }
};
