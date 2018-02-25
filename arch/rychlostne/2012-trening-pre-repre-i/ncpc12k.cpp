#include "../../../l/lib.h"
#include "../../../l/graph.h"

class ncpc12k {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> S(N);
        vector2<int> O(N, N-1);
        for (int i = 0; i < N; ++i) {
            cin >> S[i] >> O[i];
        }

        for (int T = N - 2; T >= 0; --T) {
            TwoSat R(N);
            for (int L = T; L < N-1; ++L) {
                for (int i = 0; i < N; ++i) {
                    int s = O[i][L] - 1;
                    if (S[i] == S[s]) {
                        R.addClause(i, true, s, true);
                        R.addClause(i, false, s, false);
                    } else if (S[i] == (S[s] + 1) % 3) {
                        R.addClause(i, false, s, true);
                    } else {
                        R.addClause(i, true, s, false);
                    }
                }
            }

            if (!R.satisfiable()) {
                cout << T+1 << endl;
                return;
            }
        }

        cout << "0\n";

    }
};
