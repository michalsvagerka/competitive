#include "../l/lib.h"
#include "../l/hungary.h"

class gridgame {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector2<int> A(N,N); cin >> A;
            Hungary<int> H(A);
            cout << H.minCost() << '\n';
        }
    }
};
