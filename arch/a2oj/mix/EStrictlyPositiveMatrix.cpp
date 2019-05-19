#include "../l/lib.h"
 #include "../l/graph.h"

class EStrictlyPositiveMatrix {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector2<int> A(N, N); cin >> A;
    DirectedGraph D(N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i != j && A[i][j]) {
                D.addEdge(i, j);
            }
        }
    }
    D.calcStronglyConnectedComponents();
    for (int i = 0; i < N; ++i) {
        if (D.SCC[i] != D.SCC[0]) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}
};
