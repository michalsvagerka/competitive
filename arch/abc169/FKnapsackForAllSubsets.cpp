#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;

class FKnapsackForAllSubsets {
public:
    void solve(istream& cin, ostream& cout) {
        int N, S;
        cin >> N >> S;
        vector<int> A(N); cin >> A;
        vector2<FF> D(N+1, S+1, 0);
        D[0][0] = 1;
        for (int i = 0; i < N; ++i) {
            for (int s = 0; s <= S; ++s) {
                D[i+1][s] += 2*D[i][s];
                if (s + A[i] <= S) {
                    D[i+1][s+A[i]] += D[i][s];
                }
            }
        }
        cout << D[N][S] << '\n';
    }
};
