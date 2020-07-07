#include "../../../l/lib.h"

class BReversingEncryption {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        string S; cin >> S;
        for (int i = 1; i <= N; ++i) {
            if (N%i == 0) {
                reverse(S.begin(),S.begin()+i);
            }
        }
        cout << S << endl;
    }
};
