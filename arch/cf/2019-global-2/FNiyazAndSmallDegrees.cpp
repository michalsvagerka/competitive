#include "../l/lib.h"
#include "../l/fenwick.h"

class FNiyazAndSmallDegrees {
public:
    int N, X;
    vector<map<int, int>> E, ZZ;
    vector<int> D, V;
    vector<Fenwick<int>> CNT;
    vector<Fenwick<ll>> SUM;

    void add(int hiDeg, int idInFenwick, int cost) {
        CNT[hiDeg].add(idInFenwick, 1);
        SUM[hiDeg].add(idInFenwick, cost);
    }

    ll sumLowest(int hiDeg, int cnt) {
        if (cnt <= 0) return 0LL;
        int id = CNT[hiDeg].max_lower(cnt);
        if (id == CNT[hiDeg].N - 1) return 1e12;
        return SUM[hiDeg].sum(id+1);
    }

    pair<ll,ll> solve(int u, int p, ll parentCost) {
        V[u] = X;
        ll tot = 0;
        vector<ll> Q;
        for (pii v: E[u]) {
            if (v.x != p) {
                auto sol = solve(v.x, u, v.y);
                tot += sol.x;
                Q.push_back(sol.y);
            }
        }
        sort(Q.begin(),Q.end());

        ll ans1 = 1e12, ans2 = 1e12, pref = 0;
        vector<ll> sumL(Q.size() + 2);
        int toRem = D[u] - X;
        for (int i = 0; i <= Q.size()+1; ++i) sumL[i] = sumLowest(u, toRem - i);

        for (int i = 0; i <= Q.size(); ++i) {
            ans1 = min(ans1, pref + sumL[i]);
            ans2 = min(ans2, pref + sumL[i + 1]);
            if (i != Q.size()) pref += Q[i];
        }

        return {tot + ans1, ans2 - ans1 + parentCost};
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        D.resize(N);
        ZZ.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int a, b, c; cin >> a >> b >> c;
            --a; --b;
            E[a][b] = c;
            E[b][a] = c;
        }

        map<int, vector<int>> ByDeg;
        for (int i = 0; i < N; ++i) {
            D[i] = E[i].size();
            ByDeg[D[i]].push_back(i);
            vector<pii> ByCost;
            for (pii e: E[i]) ByCost.emplace_back(e.y, e.x);
            sort(ByCost.begin(), ByCost.end());
            for (int j = 0; j < D[i]; ++j) ZZ[i][ByCost[j].y] = j;
            CNT.emplace_back(D[i], 0);
            SUM.emplace_back(D[i], 0LL);
        }
        V.assign(N, -1);

        vector<ll> Cost(N, 0LL);
        for (X = 0; X < N; ++X) {
            for (int v: ByDeg[X]) {
                for (pii q: E[v]) {
                    add(q.x, ZZ[q.x][v], q.y);
                    E[q.x].erase(v);
                }
            }
            ByDeg.erase(X);

            for (auto &bd: ByDeg) {
                for (int v : bd.y) {
                    if (V[v] != X) {
                        auto ans = solve(v, -1, 1e12);
                        Cost[X] += ans.x + min(0LL, ans.y);
                    }
                }
            }
        }

        cout << Cost;
    }
};
