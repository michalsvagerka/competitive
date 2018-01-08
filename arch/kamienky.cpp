#include "../l/lib.h"
// #include "../l/mod.h"

class kamienky {
public:
    map<vector<int>, int> C;

    bool islosing(const vector<int> &Z) {
        int N = Z.size();
        int g = 0;
        for (int i = 1-N%2; i < N; i+=2) {
            g^=Z[i]-(i==0?i:Z[i-1]);
        }
        return g == 0;
    }

    void solve(istream& cin, ostream& cout) {
        int P; cin >> P;
        for (int p = 0; p < P; ++p) {
            int N; cin >> N;
            vector<int> A(N); cin >> A;
            if (islosing(A)) cout << "Anicka\n";
            else {
                cout << "Rasto ";
                bool found = false;
                for (int i = 0; i < N && !found; ++i) {
                    int lo = i==0?0:A[i-1], hi = A[i];
                    for (int j = lo; j < hi && !found; ++j) {
                        A[i] = j;
                        if (islosing(A)) {
                            cout << i+1 << ' ' << hi - j << '\n';
                            found = true;
                        }
                    }
                    A[i] = hi;
                }
            }
        }
    }
};

