#include "../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:

    int N;
    vector<set<int>> E;




void solve(istream& cin, ostream& cout) {
    cin >> N;
    E.resize(N);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        E[u].insert(v);
        E[v].insert(u);
    }

    vector<int> A(N); cin >> A;
    for (int&a:A) --a;
//    if (A[0] != 0) { cout << "No\n"; return; }
    vector<bool> V(N, false);
    V[0] = true;
    int r = 1;
    for (int q = 0; q < N; ++q) {
        int u = A[q];
        while (r < N && E[u].find(A[r]) != E[u].end()) {
            E[u].erase(A[r]);
            V[A[r]] = true;
            ++r;
        }
        for (int v:E[u]) {
            if (!V[v]) {
                cout << "No\n";
                return;
            }
        }
    }
    cout << "Yes\n";
}
};
