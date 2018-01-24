#include "../l/lib.h"
// #include "../l/mod.h"

class f13buridan {
public:
    bool valid(const pii&a) {
        return a.x <= a.y;
    }

    pii any(const pii&a, const pii&b) {
        return {max(a.x,b.x),min(a.y,b.y)};
    }

    pii neutral() {
        return {0,1000000000};
    }

    bool isNeutral(const pii&a) {
        return a.x == 0 && a.y == 1000000000;
    }

    pii invalid() {
        return {1,0};
    }

    pii both(const pii&a, const pii&b) {
        if (isNeutral(a)) return b;
        else if (isNeutral(b)) return a;
        else if (valid(a) && valid(b)) {
            return {a.x + b.x, a.y + b.y};
        } else {
            return invalid();
        }
    }

    int N; vector<vector<int>> E;
    vector<vector<pii>> O;
    vector<bool> Ans;
    vector<pii> L;

    pii dfs1(int u, int p) {
        pii ans = neutral();
        for (int v: E[u]) {
            if (v!=p) {
                pii x = dfs1(v, u);
                O[u].push_back(x);
                ans = any(ans, x);
            }
        }

        ans = both(ans, L[u]);
        return ans;
    }
    
    void dfs2(int u, int p, pii fromAbove) {
        unsigned long m = O[u].size();
        vector<pii> pref(m+1, fromAbove), suf(m+1, neutral());
        for (int i = 0; i < m; ++i) {
            pref[i+1] = any(pref[i], O[u][i]);
            suf[m-i-1] = any(suf[m-i], O[u][m-1-i]);
        }

        int i = 0;
        for (int v:E[u]) {
            if (v!=p) {
                dfs2(v, u, both(L[u], any(pref[i], suf[i+1])));
                ++i;
            }
        }


        pii me = both(L[u], pref[m]);

        Ans[u] = me.x <= me.y;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N); O.resize(N); Ans.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int a,b; cin >> a >> b; --a; --b;
            E[a].push_back(b);
            E[b].push_back(a);
        }
        L.resize(N);
        for (int i = 0; i < N; ++i) {
            cin >> L[i].x >> L[i].y;
        }
        
        dfs1(0, -1);
        dfs2(0, -1, neutral());

        cout << Ans;
    }
};
