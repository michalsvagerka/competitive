#include "../l/lib.h"

class BEvenDegrees {
public:
    vector<vector<int>> F;
    vector<pii> Ans;
    vector<bool> V;
    set<pii> Proc;
    
    bool dfs(int u, int p) {
        V[u] = true;
        vector<int> Use;
        for (int v : F[u]) {
            if (Proc.count({v,u}) || Proc.count({u,v})) {
                // pass
            } else if (V[v]) {
                Proc.insert({v,u});
                Proc.insert({u,v});
                Use.push_back(v);
            } else {
                Proc.insert({v,u});
                Proc.insert({u,v});
                if (dfs(v, u)) {
                    Use.push_back(v);
                }
            }
        }
        
//        cerr << u << ":" << Use;
        int M = Use.size();
        for (int i = 0; i + 1 < M; i += 2) {
//            cerr << "put " << u << ' ' << Use[i] << ' ' << Use[i+1] << endl;
            Ans.emplace_back(u+1, Use[i]+1);
            Ans.emplace_back(u+1, Use[i+1]+1);
        }
        if (M%2 == 1) {

//            cerr << "put " << u << ' ' << Use.back() << ' ' << p << endl;
            Ans.emplace_back(u+1, Use.back()+1);
            Ans.emplace_back(u+1, p+1);
            return false;
        } else {
            return true;
        }
    }
    
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<pii> E(M); cin >> E;
        for (pii&e: E) { e.x--; e.y--; }
        if (M % 2 == 1) {
            cout << "-1\n";
            return;
        }
        F.resize(N);
        V.assign(N, false);
        for (pii e:E) {
            F[e.x].push_back(e.y);
            F[e.y].push_back(e.x);
        }
        
        dfs(0, -1);
        for (pii ans: Ans) {
            cout << ans << '\n';
        }
    }
};
