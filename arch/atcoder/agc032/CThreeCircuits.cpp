#include "../l/lib.h"
#include "../l/util.h"

class CThreeCircuits {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<vector<int>> E(N);
        for (int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            --a; --b;
            E[a].push_back(b);
            E[b].push_back(a);
        }

        vector<int> C(N);
        int four = 0;
        int six = 0;

        for (int i = 0; i < N; ++i) {
            C[i] = E[i].size();
            if (C[i] % 2 == 1) {
                cout << "No\n";
                return;
            }

            if (C[i] == 4) four++;
            if (C[i] >= 6) six++;
        }

        if (six > 0 || four > 2) {
            cout << "Yes\n";
            return;
        }
        
        if (four < 2) {
            cout << "No\n";
            return;
        }
        
        
        UnionFind U(N);
        for (int i = 0; i < N; ++i) {
            for (int j: E[i]) {
                if (C[i] == 2 && C[j] == 2) {
                    U.unite(i, j);
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            if (C[i] == 4) {
                set<int> S;
                for (int j : E[i]) {
                    S.insert(U.find(j));
                }
                if (S.size() != 4) {
                    cout << "Yes\n";
                } else {
                    cout << "No\n";
                }
                return;
            }
        }
        

    }
};
