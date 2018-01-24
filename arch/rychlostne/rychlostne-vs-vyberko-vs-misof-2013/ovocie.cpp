#include "../l/lib.h"
#include "../l/graph.h"
#include "../l/segtree.h"


class ovocia {
public:
    ui N,Q,C;
    vector<vector<ui>> edges;
    vector<ui> color,Enter,Exit,back;
    unordered_map<ui, set<ui>> colorSet;
    Fenwick<int> fen;
    Tree tree;

    void dfs(ui u, ui &t) {
        Enter[u] = t;
        back[t] = u;
        if (color[u]) {
            colorSet[color[u]].insert(t);
            fen.add(t, 1);
        }
        ++t;
        for (ui v: edges[u]) dfs(v, t);
        Exit[u] = t;
    }

    void add(ui prev, ui cur, ui next, int val) {
        ui p = prev != -1 ? tree.lca(back[prev], cur) : -1;
        ui n = next != -1 ? tree.lca(cur, back[next]) : -1;
        ui t = p;
        if (n != -1 && (p == -1 || tree.depth(p) < tree.depth(n))) t = n;
        if (t != -1) fen.add(Enter[t], -val);
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> Q;
        edges.resize(N);
        color.resize(N);
        Enter.resize(N);
        Exit.resize(N);
        tree = Tree(N);
        fen = Fenwick<int>(N);
        back.resize(N);

        for (ui i = 0; i < N; ++i) {
            ui p; cin >> p;
            if (p == 0) {
                tree.setRoot(i);
            } else {
                edges[p-1].push_back(i);
                tree.addEdge(p-1, i);
            }
        }

        cin >> color;

        C = 0;
        dfs(tree.root(), C);

        for (auto &f: colorSet) {
            ui prev = -1;
            for (ui i: f.y) {
                add(prev, i, -1, 1);
                prev = i;
            }
        }

        int error = 0, correct = 0;
        for (ui q = 0; q < Q; ++q) {
            char t; cin >> t;
            if (t == 'z') {
                ui n,f;
                cin >> n >> f;
                --n;
                if (color[n] == f) continue;
                ui dfsId = Enter[n];
                auto &from = colorSet[color[n]];
                auto it = from.find(dfsId);
                ui prevVal = (it != from.begin()) ? *prev(it) : -1;
                ui nextVal = (next(it) != from.end()) ? *next(it) : -1;
                add(prevVal, n, nextVal, -1);
                from.erase(it);

                auto &to = colorSet[f];
                to.insert(dfsId);
                it = to.find(dfsId);
                prevVal = (it != to.begin()) ? *prev(it) : -1;
                nextVal = (next(it) != to.end()) ? *next(it) : -1;
                add(prevVal, n, nextVal, 1);
                color[n] = f;
            } else {
                int n; cin >> n; --n;
                ui fast = fen.range(Enter[n], Exit[n]-1);
                cout << fast << endl;
            }
        }
    }
};
