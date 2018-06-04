#include "../../../l/lib.h"
#include "../../../l/graph.h"

class lovelymatrix {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector2<int> A(N, M); cin >> A;
        DirectedGraph G(1e5+1e4);
        int s = M;
        for (int i = 0; i < N; ++i) {
            map<int, vector<int>> W;
            for (int j = 0; j < M; ++j) if (A[i][j] != -1) W[A[i][j]].push_back(j);
            for (auto&w:W) {
                for (auto&v:w.y) {
                    G.addEdge(s, v);
                    G.addEdge(v, s+1);
                }
                ++s;
            }

            ++s;
        }

        G.calcStronglyConnectedComponents();
        auto P = G.stronglyConnectedPermutation();
        P.resize(s);
        vector<int> Ans;
        for (int &p: P) {
            if (p < M) {
                if (G.stronglyConnectedComponent(p) != p) {
                    cout << "-1\n";
                    return;
                } else {
                    Ans.push_back(p+1);
                }
            }
        }
        reverse(Ans.begin(),Ans.end());
        cout << Ans;
    }
};
