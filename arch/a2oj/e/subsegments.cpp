#include "../../../l/lib.h"
// #include "../l/mod.h"

class subsegments {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> A(N); cin >> A;
        map<int,int> C;
        set<int> O;
        for (int i = 0; i < K; ++i) {
            int c = ++C[A[i]];
            if (c == 1) O.insert(A[i]);
            else if (c == 2) O.erase(A[i]);
        }

        if (O.empty()) {
            cout << "Nothing\n";
        } else {
            cout << *O.rbegin() << '\n';
        }

        for (int i = K; i < N; ++i) {
            int d = --C[A[i-K]];
            if (d == 1) O.insert(A[i-K]);
            else if (d == 0) O.erase(A[i-K]);

            int c = ++C[A[i]];
            if (c == 1) O.insert(A[i]);
            else if (c == 2) O.erase(A[i]);

            if (O.empty()) {
                cout << "Nothing\n";
            } else {
                cout << *O.rbegin() << '\n';
            }
        }

    }
};
