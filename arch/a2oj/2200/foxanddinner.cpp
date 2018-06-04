#include "../../../l/lib.h"
#include "../../../l/primes.h"
#include "../../../l/graph.h"

class foxanddinner {
public:
    void solve(istream& cin, ostream& cout) {
        ui N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<pii> Odd, Even;
        for (int i = 0; i < N; ++i) {
            if (A[i]%2) {
                Odd.push_back({A[i],i+1});
            } else {
                Even.push_back({A[i],i+1});
            }
        }

        if (Odd.size() != Even.size()) {
            cout << "Impossible\n";
            return;
        }

        Sieve S{ui(3e4)};

        vector2<int> M(2, N, -1);
        for (int t = 0; t < 2; ++t) {

            Bipartite B{N / 2, N / 2};
            for (int i = 0; i < N / 2; ++i) {
                for (int j = 0; j < N / 2; ++j) {
                    if (S[Odd[i].x + Even[j].x] && M[0][i] != j+N/2) {
                        B.addEdge(i, j + N / 2);
                    }
                }
            }

            if (B.matchingSize() != N/2) {
                cout << "Impossible\n";
                return;
            }
            for (int i = 0; i < N/2; ++i) {
                M[t][i] = B.matched(i);
                M[t][B.matched(i)] = i;
            }
        }

        vector<vector<int>> CH;
        vector<bool> U(N, false);
        for (int j = 0; j < N/2; ++j) {
            if (U[j]) continue;
            vector<int> Q;
            for (int i = j; !U[i]; ) {
                U[i] = true;
                Q.push_back(i<N/2?Odd[i].y:Even[i-N/2].y);
                i = U[M[0][i]] ? M[1][i] : M[0][i];
            }
            CH.push_back(Q);
        }

        cout << CH.size() << endl;
        for (auto&ch: CH) {
            cout << ch.size() << ' ' << ch;
        }


    }
};
