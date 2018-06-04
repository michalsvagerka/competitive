#include "../../../l/lib.h"
// #include "../l/mod.h"

class B {
public:
    void solve(istream& cin, ostream& cout) {
        int A,B; cin >> A >> B;
        stringstream ss; ss << A;
        string S = ss.str();
        sort(S.begin(),S.end());
        int ans = -1;
        do {
            if (S[0] != '0') {
                stringstream w(S);
                int c; w >> c;
                if (c <= B) {
                    ans = max(ans, c);
                }
            }
        } while (next_permutation(S.begin(),S.end()));
        cout << ans << endl;
    }
};
