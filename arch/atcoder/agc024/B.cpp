#include "../../../l/lib.h"
// #include "../l/mod.h"

class B {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<int> L(N+1, 0);
        for (int i = 0; i < N; ++i) {
            L[A[i]] = L[A[i]-1]+1;
        }

        cout << N-*max_element(L.begin(),L.end()) << endl;
    }
};
