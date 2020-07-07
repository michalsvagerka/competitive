#include "../../../l/lib.h"

class ACardGame {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int i = 0; i < T; ++i) {
            int N, K1, K2; cin >> N >> K1 >> K2;
            vector<int> A(K1), B(K2); cin >> A >> B;
            if (count(A.begin(),A.end(),N) == 1) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
};
