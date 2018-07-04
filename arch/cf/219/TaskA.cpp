#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> S(N); cin >> S;
    sort(S.begin(),S.end());
    cout << N - bsh(0, N/2, [&](int s) {
        for (int i = 0; i < s; ++i) {
            if (2*S[i] > S[N-s+i]) return false;
        }
        return true;
    }) << '\n';
}
};
