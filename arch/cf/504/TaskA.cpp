#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    string S, T; cin >> S >> T;
    if (S == T) {
        cout << "YES\n";
        return;
    }

    int star = -1;
    for (int i = 0; i < N; ++i) if (S[i] == '*') star = i;
    if (star == -1) {
        cout << "NO\n";
        return;
    }

    int pref = 0, suf = 0;
    while (pref < N && pref < M && S[pref] == T[pref]) ++pref;
    while (suf < N && suf < M && S[N-1-suf] == T[M-1-suf]) ++suf;
    if (suf + pref + 1 == N && suf + pref <= M) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
};
