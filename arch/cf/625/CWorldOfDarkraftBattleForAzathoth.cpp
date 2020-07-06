#include "../l/lib.h"
#include "../l/nsegtree.h"

class CWorldOfDarkraftBattleForAzathoth {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M, P; cin >> N >> M >> P;
        vector<pii> W(N); cin >> W;
        vector<pii> A(M); cin >> A;
        vector2<int> E(P, 3); cin >> E;
        set<int> Comp;
        for (pii w: W) Comp.insert(w.x);
        for (pii a: A) Comp.insert(a.x);
        for (auto e: E) {
            Comp.insert(e[0]);
            Comp.insert(e[1]+1);
        }
        int G = Comp.size();
        vector<int> CompX(Comp.begin(),Comp.end());
        map<int,int> CompM;
        for (int i = 0; i < G; ++i) CompM[CompX[i]] = i;
        for (pii&w: W) w.x = CompM[w.x];
        for (pii&a: A) a.x = CompM[a.x];
        for (auto&e: E) {
            e[0] = CompM[e[0]];
            e[1] = CompM[e[1]+1];
        }

        ll INF = 2e9;
        vector<ll> ArmorCost(G, -INF);
        for (pii a: A) ArmorCost[a.x] = max(ArmorCost[a.x], -1LL*a.y);
        for (int i = G-1; i > 0; --i) ArmorCost[i-1] = max(ArmorCost[i-1], ArmorCost[i]);
        for (int i = 0; i < G; ++i) ArmorCost[i] += INF;

        LAddMaxTree<ll> Tree(ArmorCost, 0LL, 0LL);
        sort(W.begin(),W.end());
        sort(E.begin(),E.end(), [](const vector<int>&a, const vector<int>&b) { return a[0] < b[0]; });
        int i = 0, j = 0;
        ll ans = -INF;
        while (i != W.size() || j != E.size()) {
            if (i == W.size() || (i != W.size() && j != E.size() && W[i].x > E[j][0])) {
                Tree.put(E[j][1], G-1, E[j][2]);
                j++;
            } else {
                ll cur = Tree.get(0,G-1)-INF-W[i].y;
                ans = max(ans, cur);
                i++;
            }
        }
        cout << ans << '\n';
    }
};
