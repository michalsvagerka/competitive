#include "../l/lib.h"
#include "../l/graph.h"
#include "../l/nsegtree.h"

void CombineTag(int &a, int b) { a += b; }
void ApplyTag(pii &a, int b, ui) { a.x += b; }
pii CombineValues(pii a, pii b) { if (a.x == b.x) return {a.x, a.y+b.y}; else if (a.x < b.x) return a; else return b; }

using ZeroCountTree = LSegTree<pii, int, CombineTag, ApplyTag, CombineValues>;

class boat {
public:
    vector<vector<int>> E;
    vector<int> Enter, Exit, Other;
//    vector<int> Seg;
    vector<bool> Up, Down;
    TreeX Tree;
    ZeroCountTree SegT{2, {0,1}, 0};
    int N;
    ll tot;

    int dwn(int u, int v) {
        return Tree.la(u, Tree.depth(u) - Tree.depth(v) - 1);
    }

    void dfs(int u, int p) {
        int w = -1;
        if (Other[u] != -1) {
            if (Up[u]) {
                tot += cnt();
                w = dwn(Other[u], u);
            } else if (Down[u]) {
                int v = dwn(u, Other[u]);
                add(0, N, 1);
                add(Enter[v], Exit[v], -1);
                tot += cnt();
            } else {
                // add for self and children
                add(Enter[Other[u]], Exit[Other[u]], 1);
                tot += cnt();
            }
        } else {
            tot += cnt();
        }

        for (int v : E[u]) {
            if (v != p) {
                if (w == v) add(Enter[Other[u]], Exit[Other[u]], -1);
                dfs(v, u);
                if (w == v) add(Enter[Other[u]], Exit[Other[u]], 1);
            }
        }

        if (Other[u] != -1) {
            if (Up[u]) {

            } else if (Down[u]) {
                int v = dwn(u, Other[u]);
                add(Enter[v], Exit[v], 1);
                add(0, N, -1);
            } else {
                // add for self and children
                add(Enter[Other[u]], Exit[Other[u]], -1);
            }
        }
    }

    void add(int i, int j, int c) {
        SegT.put(i, j-1, c);
//        for (int k = i; k < j; ++k) Seg[k] += c;
    }

    int cnt() {
        pii ans = SegT.get(0, N-1);
        if (ans.x == 0) return ans.y; else return 0;
//        int ans = 0;
//        for (int i = 0; i < N; ++i) ans += Seg[i] == 0;
//        return ans;
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            cin >> N;
            cerr << N << endl;
            vector<string> S(N); cin >> S;
            E.clear(); E.resize(N);
            for (int i = 0; i < N-1; ++i) {
                int x, y;
                cin >> x >> y;
                --x;
                --y;
                E[x].push_back(y);
                E[y].push_back(x);
            }

            map<string, vector<int>> W;
            for (int i = 0; i < N; ++i) if (S[i] != "-") W[S[i]].push_back(i);

            Other.assign(N, -1);
            for (auto &w: W) {
                if (w.y.size() == 2) {
                    int a = w.y[0], b = w.y[1];
                    Other[a] = b;
                    Other[b] = a;
                }
            }

            DFSOrder D(E);
            Enter = D.enter();
            Exit = D.exit();

            Tree = TreeX{N};
            for (int i = 0; i < N; ++i) {
                for (int j : E[i]) {
                    if (i < j) Tree.addEdge(i, j);
                }
            }
            Tree.calcLA();
            Up.assign(N, false);
            Down.assign(N, false);
            for (int i = 0; i < N; ++i) {
                if (Other[i] != -1 && Tree.lca(i, Other[i]) == i) {
                    Up[i] = true;
                    Down[Other[i]] = true;
                }
            }

            SegT = ZeroCountTree(N, {0,1}, 0);
            for (int i = 0; i < N; ++i) {
                if (Up[i]) {
                    add(Enter[Other[i]], Exit[Other[i]], 1);
                }
            }

            tot = 0;
            dfs(0, -1);
            tot -= N;
            cout << "Case #" << t+1 << ": " << tot << endl;
        }
    }
};
