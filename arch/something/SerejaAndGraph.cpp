#include "../l/lib.h"
// #include "../l/mod.h"

class SerejaAndGraph {
public:
    int N, M;
    vector<vector<int>> E;
    vector<int> O;
    vector<bool> V;
    
    bool match(int u) {
        if (V[u]) return false;
        V[u] = true;
        
        for (int v : E[u]) {
            if (O[v] == -1) {
                if (!V[v]) {
                    O[u] = v;
                    O[v] = u;
                    return true;
                }
            } else {
                if (match(O[v])) {
                    O[u] = v;
                    O[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            cin >> N >> M;
            E.assign(N, {});
            for (int i = 0; i < M; ++i) {
                int a, b; cin >> a >> b; --a; --b;
                E[a].push_back(b);
                E[b].push_back(a);
            }
            O.assign(N, -1);
            bool ch = true;
            while (ch) {
                ch = false;
                for (int k = 0; k < N; ++k) {
                    if (O[k] == -1) {
                        V.assign(N, false);
                        ch |= match(k);
                    }
                }
            }
            
            if (count(O.begin(),O.end(),-1) == 0) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
};
