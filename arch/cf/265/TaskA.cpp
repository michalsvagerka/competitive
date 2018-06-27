#include "../../../l/lib.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N, P; cin >> N >> P;
    string S; cin >> S;
    reverse(S.begin(),S.end());

    bool fail = false;
    auto addTo = [&](int x) {
        while (true) {
            ++S[x];
            if (S[x] == 'a' + P) {
                S[x++] = 'a';
                if (x == N) {
                    return false;
                }
            } else {
                return true;
            }
        }
    };

    if (!addTo(0)) { cout << "NO\n"; return; }

    while (true) {
        bool p = false;
        for (int i = N-1; !p && i > 0; --i) {
            if (i-1 >= 0 && S[i] == S[i-1]) {
                p = true;
                if (!addTo(i-1)) { cout << "NO\n"; return; }
                for (int j = 0; j < i-1; ++j) S[j] = 'a';
            }
            if (i-2 >= 0 && S[i] == S[i-2]) {
                p = true;
                if (!addTo(i-2)) { cout << "NO\n"; return; }
                for (int j = 0; j < i-2; ++j) S[j] = 'a';
            }
        }

        if (!p) {
            reverse(S.begin(),S.end());
            cout << S << '\n';
            return;
        }
    }
}
};
