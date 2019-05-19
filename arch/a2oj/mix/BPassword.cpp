#include "../l/lib.h"
 #include "../l/string.h"

class BPassword {
public:
void solve(istream& cin, ostream& cout) {
    string S; cin >> S;
    int N = S.size();
    auto P = PrefixFunction(S);
    if (P[N-1] != 0) {
        if (count(P.begin(),P.end(),P[N-1]) >= 2) {
            cout << S.substr(0,P[N-1]) << '\n';
            return;
        } else {
            int p = P[P[N-1]-1];
            if (p != 0) {
                cout << S.substr(0,p) << '\n';
                return;
            }
        }
    }

    cout << "Just a legend\n";
}
};
