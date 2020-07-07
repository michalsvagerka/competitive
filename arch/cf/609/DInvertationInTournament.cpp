#include "../../../l/lib.h"
#include "../../../l/graph.h"
#include "../../../l/mod.h"

typedef Field<998244353> FF;

class DInvertationInTournament {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<string> A(N); cin >> A;
        DirectedGraph G(N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[i][j] == '1') G.addEdge(i, j);
            }
        }

        // failed => there cannot be too many vertices
        if (N <= 16) {
            int lo = 100;
            int cnt = 0;
            for (int i = 0; i < (1 << N); ++i) {
                int w = __builtin_popcount(i);
                if (w > lo) continue;

                DirectedGraph H(N);
                for (int j = 0; j < N; ++j) {
                    for (int k = 0; k < N; ++k) {
                        if (A[j][k] == '1') {
                            int a = j, b = k;
                            if (i & 1 << j) swap(a, b);
                            if (i & 1 << k) swap(a, b);
                            H.addEdge(a, b);
                        }
                    }
                }
                H.calcStronglyConnectedComponents();
                auto PP = H.stronglyConnectedPermutation();
                if (H.SCC[PP[0]] == H.SCC[PP.back()]) {
                    if (w == lo) cnt++;
                    else {
                        lo = w;
                        cnt = 1;
                    }
                }
            }


            if (lo == 100) {
                cout << -1 << endl;
                return;
            }

            FF ans = cnt;
            for (int i = 1; i <= lo; ++i) ans *= i;
            cout << lo << ' ' << ans << endl;
            return;
        }
        
//      

        vector<int> In(N, 0), Out(N, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[i][j] == '1') {
                    Out[i]++;
                    In[j]++;
                }
            }
        }

        G.calcStronglyConnectedComponents();

        auto P = G.stronglyConnectedPermutation();

        int first = G.SCC[P[0]];
        int last = G.SCC[P.back()];
        if (first == last) {
            cout << "0 1\n";
            return;
        }

        // first have large indegree, last have large outdegree

        int cnt = 0;
        for (int i = 0; i < N; ++i) {
            if (G.SCC[i] != first && G.SCC[i] != last) ++cnt;
        }

        if (cnt != 0) {
            // more than 2 SCC
            for (int i = 0; i < N; ++i) {
                if ((G.SCC[i] == first || G.SCC[i] == last) && In[i] < N-2 && Out[i] < N-2) cnt++;
            }
            
            cout << 1 << ' ' << cnt << '\n';
        } else {
            // exactly two SCC
            for (int i = 0; i < N; ++i) {
                if ((G.SCC[i] == first || G.SCC[i] == last) && In[i] < N-2 && Out[i] < N-2) cnt++;
            }
            
            if (cnt != 0) {
                cout << 1 << ' ' << cnt << '\n';
                return;
            }

            cout << -1 << endl;
            
        }
    }
};
