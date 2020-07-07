#include "../../../l/lib.h"

class GSubsetWithZeroSum {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector<int> A(N); cin >> A;
            for (int i = 0; i < N; ++i) {
                A[i] = i-A[i];
            }
            vector<int> P{0};
            vector<int> U(N, false);
            U[0] = true;
            int v = 0;
            vector<int> Ans;
            while (true) {
                v = A[v];
                if (U[v]) {
                    while (P.back() != v) {
                        Ans.push_back(P.back()+1);
                        P.pop_back();
                    }
                    Ans.push_back(v+1);
                    break;
                } else {
                    U[v] = true;
                    P.push_back(v);
                }
            }
            cout << Ans.size() << '\n' << Ans;

        }
    }
};
