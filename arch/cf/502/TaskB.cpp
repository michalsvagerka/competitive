#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    ll N; cin >> N;
    string S, T; cin >> S >> T;
    ll a = 0, b = 0, c = 0, d = 0;
    for (int i = 0; i < N; ++i) {
        if (S[i] == '0' && T[i] == '0') ++a;
        if (S[i] == '1' && T[i] == '0') ++b;
        if (S[i] == '0' && T[i] == '1') ++c;
        if (S[i] == '1' && T[i] == '1') ++d;
    }
    
    cout << a*b + a*d + b*c << '\n';
}
};
