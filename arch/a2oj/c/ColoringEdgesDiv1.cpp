#include "../l/lib.h"
 #include "../l/random.h"
#include "../l/util.h"

class ColoringEdgesDiv1 {
public:

    vector <int> findColoring(int n, vector <int> X, vector <int> Y) {
        int m = X.size();
        vector<int> C(m, 0), Z(m);
        iota(Z.begin(),Z.end(),0);
        random_int R(0,1);
        while (true) {
            shuffle(Z.begin(),Z.end(),rng);
            UnionFind A(n), B(n);
            bool hasCycle = false;
            for (int i = 0; i < m; ++i) {
                if (R(rng) && B.unite(X[Z[i]], Y[Z[i]])) {
                    C[Z[i]] = 1;
                } else if (A.unite(X[Z[i]],Y[Z[i]])) {
                    C[Z[i]] = 0;
                } else if (B.unite(X[Z[i]], Y[Z[i]])) {
                    C[Z[i]] = 1;
                } else {
                    hasCycle = true;
                    break;
                }
            }
            if (!hasCycle) return C;
        }
    }


void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    int M = 3*N/2;
    vector<int> X(M), Y(M); cin >> X >> Y;
    cout << findColoring(N, X, Y);
}
};
