#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> D(N), X(N);
    vector<int> Q;
    for (int i = 0; i < N; ++i) {
        cin >> D[i] >> X[i];
        if (D[i] == 1) {
            Q.push_back(i);
        }
    }

    vector<pii> E;
    for (int i = 0; i < Q.size(); ++i) {
        if (D[Q[i]] == 0) continue;

        E.push_back({Q[i], X[Q[i]]});
        X[X[Q[i]]] ^= Q[i];
        D[Q[i]]--;
        if (--D[X[Q[i]]] == 1) {
            Q.push_back(X[Q[i]]);
        }
        X[Q[i]] = 0;
    }

    cout << E.size() << '\n';
    for (pii e:E) cout << e << '\n';
}
};
