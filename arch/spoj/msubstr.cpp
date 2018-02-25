#include "../../l/lib.h"
#include "../../l/eertree.h"

class msubstr {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            string S; cin >> S;
            Eertree<char> E(S);
            vector<int> L(S.size()+1, 0);
            for (const auto& n : E.V) if (n.length > 0) L[n.length] += n.count;
            for (int l = S.size(); l > 0; --l) {
                if (L[l]) {
                    cout << l << ' ' << L[l] << '\n';
                    break;
                }
            }
        }
    }
};
