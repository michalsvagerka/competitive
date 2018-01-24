#include "../l/lib.h"
// #include "../l/mod.h"

class t2techtree {
public:
    vector<vector<int>> E;
    vector<int> V;

    vector<int> solve(int u) {
        vector<int> L{0};
        for (int v: E[u]) {
            auto W = solve(v);
            vector<int> T(W.size()+L.size()-1,-1000000000);
            for (int i = 0; i < W.size(); ++i) {
                for (int j = 0; j < L.size(); ++j) {
                    T[i+j] = max(T[i+j], W[i] + L[j]);
                }
            }
            swap(T,L);
        }
        vector<int> S(L.size()+1, 0);
        for (int i = 0; i < L.size(); ++i) {
            S[i+1] = V[u] + L[i];
        }
        return S;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        V.resize(N); E.resize(N);
        for (int i = 0; i < N; ++i) {
            int p; cin >> p >> V[i];
            if (p--) E[p].push_back(i);
        }

        for (int s: solve(0)) {
            cout << s << '\n';
        }
    }
};
