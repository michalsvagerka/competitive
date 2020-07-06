#include "../l/lib.h"

class A2AddOnATreeRevolution {
public:
    int N, L;
    vector<vector<pii>> E;
    vector<vector<int>> Ans;
    map<pii, int> X;
    bool fail;

    void put(int a, int b, int c) {
        X[{min(a,b),max(a,b)}] += c;
    }

    int get(int a, int b) {
        return X[{min(a,b),max(a,b)}];
    }

    void add(int a, int b, int x) {
        add(a, -1, b, x);
        Ans.push_back({a+1,b+1,x});
    }

    bool add(int u, int p, int b, int x) {
        if (u == b) return true;
        for (pii v: E[u]) {
            if (v.x != p) {
                put(u,v.x,x);
                if (add(v.x,u,b,x)) return true;
                put(u,v.x,-x);
            }
        }
        return false;
    }

    int leaf(int u, int p) {
        if (E[u].size() == 1) {
            return u;
        }

        for (pii v: E[u]) {
            if (v.x != p) return leaf(v.x, u);
        }
    }

    void process(int u, int v, int val) {
        if (val == 0) return;
        vector<int> Children;
        for (pii w: E[v]) if (w.x != u) Children.push_back(w.x);
        if (Children.size() == 0) {
            // leaf => ok
            add(L, v, val);
        } else if (Children.size() == 1) {
            fail = true;
        } else {
            if (val % 2 == 1) {
                fail = true;
            } else {
                int l1 = leaf(Children[0], v);
                int l2 = leaf(Children[1], v);
                add(L, l1, val/2);
                add(L, l2, val/2);
                add(l1, l2, -val/2);
            }
        }
    }

    void dfs(int u, int p) {
        for (pii v: E[u]) {
            if (v.x != p) {
                dfs(v.x, u);
                process(u, v.x, v.y-get(u,v.x));
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u,v,val; cin >> u >> v >> val; --u; --v;
            E[u].push_back({v, val});
            E[v].push_back({u, val});
        }

        L = 0;
        while (E[L].size() > 1) L++;
        fail = false;
        dfs(L, -1);
        if (fail) {
            cout << "NO\n";
        } else {
            cout << "YES\n" << Ans.size() << '\n';
            for (auto ans: Ans) cout << ans;
        }

    }
};
