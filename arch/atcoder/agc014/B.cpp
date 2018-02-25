#include "../../../l/lib.h"
// #include "../l/mod.h"

class B {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<bool> A(N, false);
        for (int i = 0; i < 2 * M; ++i) {
            int a; cin >> a; --a;
            A[a] = !A[a];
        }

        if (count(A.begin(),A.end(),true) == 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
};
