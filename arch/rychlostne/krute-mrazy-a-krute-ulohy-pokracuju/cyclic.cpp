#include <numeric>
#include "../../../l/lib.h"
// #include "../l/mod.h"

class cyclic {
public:
    bool isCyclic(const vector<int> &Z) {
        int l = 0, c = 0;
        do {
            l = Z[l] - 1;
            ++c;
        } while (l != 0);
        return c == Z.size();
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        while (N) {
            if (N%2 == 1) {
                for (int i = 2 * ((N - 1) / 2); i > 0; i -= 2) {
                    cout << i << ' ' << i + 1 << ' ';
                }
                cout << "1\n";
            } else {
                vector<int> P(N);
                P[0] = 2;
                for (int i = 0; i < N/2-1; ++i) {
                    P[2*i+1] = 2*i+3+1;
                    P[2*i+2] = 2*i+1;
                }
                P[N-1] = N-1;
                cout << P;

//                vector<int> Z(N, 0);
//                iota(Z.begin(),Z.end(),0);
//                do {
//                    int l = 0, c = 0;
//                    do {
//                        l = Z[l];
//                        ++c;
//                    } while (l != 0);
//                    bool ok = true;
//                    for (int i = 0; i < N-2; ++i) {
//                        ok &= (Z[i]<Z[i+1])^(Z[i+1]<Z[i+2]);
//                    }
//                    if (c == N && ok) {
//                        cout << Z;
//                    }
//                } while (next_permutation(Z.begin(),Z.end()));
            }

            cin >> N;
        }
    }
};
