#include "../../../l/lib.h"

class fero3 {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<string> S(N); cin >> S;
        sort(S.begin(),S.end());
        do {
            if (N < 3 || S[2] != "Fero") {
                cout << S;
            }
        } while (next_permutation(S.begin(),S.end()));
    }
};
