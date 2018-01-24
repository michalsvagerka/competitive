#include "../l/lib.h"
// #include "../l/mod.h"

class krtko {
public:
    int N;
    vector<vector<int>> E;
    vector<vector<pii>> D;
    int optDiam;;
    pii toRemove;

    pii combine(pii cur, pii sibling) {
        return {max(max(cur.x, sibling.x), cur.y+sibling.y), max(cur.y, sibling.y)};
    }

    pii plus(pii a) {
        return {max(a.x,a.y+1),a.y+1};
    }

    int result(int d1, int d2) {
        return max(1 + (d1+1)/2 + (d2+1)/2, max(d1,d2));
    }

    pii diam(int u, int p) {
        pii cur = {0,0};
        for (int v:E[u]) {
            if (v != p) {
                pii r = diam(v,u);
                D[u].push_back(r);
                cur = combine(cur, plus(r));
            }
        }
        return cur;
    }

    pii findDeepest(int u, int p, int d) {
        pii res = {d, u};
        for (int v:E[u]) {
            if (v != p && toRemove != pii{u,v} && toRemove != pii{v,u}) {
                res = max(res, findDeepest(v,u,d+1));
            }
        }
        return res;
    }

    bool findPath(int u, int p, int tar, vector<int> &path) {
        path.push_back(u);
        if (u == tar) return true;

        for (int v:E[u]) {
            if (v != p && toRemove != pii{u,v} && toRemove != pii{v,u} && findPath(v, u, tar, path)) return true;
        }

        path.pop_back();
        return false;
    }

    int findCenter(int u) {
        pii q = findDeepest(u, -1, 0);
        pii r = findDeepest(q.y, -1, 0);
        vector<int> P;
        findPath(q.y, -1, r.y, P);
        return P[P.size()/2];
    }

    void findOpt(int u, int p, pii fromAbove) {
        int m = D[u].size();
        vector<pii> pref(m+1,fromAbove), suf(m+1,{0,0});
        for (int i = 0; i < m; ++i) {
            pref[i+1] = combine(pref[i], plus(D[u][i]));
            suf[m-i-1] = combine(suf[m-i], plus(D[u][m-i-1]));

        }

        int i = 0;
        for (int v: E[u]) {
            if (v != p) {
                pii down = combine(pref[i], suf[i+1]);
                int res = result(down.x, D[u][i].x);
                if (res < optDiam) {
                    optDiam = res;
                    toRemove = {u,v};
                }

                findOpt(v,u,plus(down));
                ++i;
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        optDiam = N;
        E.resize(N);
        D.resize(N);
        for (int i = 0; i < N-1; ++i) {
            int a,b; cin >> a >> b; --a; --b;
            E[a].push_back(b);
            E[b].push_back(a);
        }

        diam(0, -1);
        findOpt(0, -1, {0, 0});
        cout << optDiam << '\n';
        cout << toRemove.x+1 << ' ' << toRemove.y+1 << '\n';
        cout << findCenter(toRemove.x)+1 << ' ' << findCenter(toRemove.y)+1 << '\n';
    }
};
