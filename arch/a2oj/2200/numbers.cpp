#include "../../../l/lib.h"
// #include "../l/mod.h"

class numbers {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        map<int,int> C;
        for (int i = 0; i < N; ++i) {
            C[A[i]]++;
        }

        int lo = C.begin()->x;
        int hi = C.rbegin()->x;

        for (int v = lo+1; v < hi; ++v) {
            if (C[v] <= C[v-1]) {
                cout << "NO\n";
                return;
            }

            C[v] -= C[v-1];
        }


        if (C[hi] == C[hi-1]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
};
