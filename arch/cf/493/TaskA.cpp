#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    ll N, X, Y; cin >> N >> X >> Y;
    string S; cin >> S;
    ll z = 0;
    for (int i = 0; i < N; ++i) {
        if (S[i] == '0') {
            z += (i==0 || S[i-1]=='1');
        }
    }

    if (z == 0) cout << 0 << endl;
    else {
        cout << Y + min(Y,X) * (z-1) << endl;
    }
}
};
