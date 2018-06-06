#include "../l/lib.h"

class signonfence {
public:
    struct Node {
        int suf, pref, best, len; const Node *l, *r;

        Node(int x) : suf(x), pref(x), best(x), len(1), l(nullptr), r(nullptr) {}
        Node(const Node &L, const Node &R) {
            l = &L;
            r = &R;
            pref = l->pref == l->len ? l->len + r->pref : l->pref;
            suf = r->suf == r->len ? r->len + l->suf : r->suf;
            best = max(max(l->best, r->best), l->suf + r->pref);
            len = l->len + r->len;
        }
    };

    const Node *build(int s) {
        if (s == 1) return new Node(1);
        else return new Node(*build(s/2), *build(s/2));
    }

    const Node getInterval(const Node *n, int l, int r, int L, int R) {
        if (L <= l && R >= r) return *n;
        int m = (l+r)/2;
        if (R <= m) return getInterval(n->l, l, m, L, R);
        else if (L >= m) return getInterval(n->r, m, r, L, R);
        else return Node(getInterval(n->l, l, m, L, R), getInterval(n->r, m, r, L, R));
    }

    const Node *update(const Node *n, int l, int r, int i) {
        if (l+1 == r) {
            return new Node(0);
        } else {
            int m = (l+r)/2;
            const Node *L = i < m ? update(n->l, l, m, i) : n->l;
            const Node *R = i < m ? n->r : update(n->r, m, r, i);
            return new Node{*L, *R};
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int NN = 1<<logceil(N);

        map<int, vector<int>> I;
        for (int i = 0; i < N; ++i) {
            int h; cin >> h;
            I[h].push_back(i);
        }

        const Node *root = build(NN);
        vector<pair<int,const Node*>> G;
        for (auto&i:I) {
            G.push_back({i.x,root});
            for (int j:i.y) root = update(root, 0, NN, j);
        }

        int M; cin >> M;
        for (int i = 0; i < M; ++i) {
            int w,l,r;
            cin >> l >> r >> w;
            cout << G[bsh(0, int(G.size())-1, [&](int i) { return w <= getInterval(G[i].y, 0, NN, l-1, r).best; })].x << '\n';
        }
    }
};
