#include "../../../l/lib.h"
// #include "../l/mod.h"

class cowsandcoolsubsequences {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> A(N); cin >> A;
        vector<int> P(N, 0);
        for (int i = 0; i < N; ++i) while (A[i] % 2 == 0) { A[i] /= 2; P[i]++; }

        vector<int> C(N, 1);
        for (int i = 1; i < N; ++i) {
            for (int j = 0; j < i; ++j) {
                if (A[j] % A[i] == 0 && (P[i] == 0 || P[j] + i - j == P[i] || P[i] < i - j)) {
                    C[i] = max(C[i], C[j]+1);
                }
            }
        }

        cout << N - *max_element(C.begin(),C.end()) << '\n';


    }
};
