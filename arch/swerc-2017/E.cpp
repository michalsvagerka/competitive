#include "../../l/lib.h"
// #include "../l/mod.h"

class E {
public:
    map<string, int> M;

    int index(string s) {
        auto it = M.find(s);
        if (it == M.end()) {
            int i = M.size()+1;
            M[s] = i;
            return i;
        } else {
            return it->y;
        }
    }

    void solve(istream& cin, ostream& cout) {
        int B, N; cin >> B >> N;
        vector<vector<pair<int,pii>>> E(10001);
        vector<bool> U(10001, false);
        for (int i = 0; i < N; ++i) {
            string dish,base,ingr; int price,prestige;
            cin >> dish >> base >> ingr >> price >> prestige;
            int dishId = index(dish);
            int baseId = index(base);
            E.resize(M.size()+1);
            E[baseId].push_back({dishId, {price,-prestige}});
            U[dishId] = true;
        }

        int R = M.size()+1;
        for (int i = 1; i < R; ++i) {
            if (!U[i]) {
                E[0].push_back({i, {0,0}});
            }
        }

        vector<pii> D(R, {1000000000, 1000000000});
        minheap<pair<int,pii>> H;
        D[0] = {0,0};
        H.push({0,{0,0}});
        while (!H.empty()) {
            auto h = H.top();
            H.pop();
            if (h.y != D[h.x]) continue;
            for (auto &e: E[h.x]) {
                pii q = {h.y.x + e.y.x, h.y.y + e.y.y};
                if (D[e.x] > q) {
                    D[e.x] = q;
                    H.push({e.x, q});
                }
            }
        }

//        for (auto &m:M) {
//            cout << m.x << ' ' << D[m.y].x << ' ' << -D[m.y].y << endl;
//        }

        vector<int> Q(B+1, -1000000000);
        Q[0] = 0;
        for (int i = 1; i < R; ++i) {
            for (int b = B - D[i].x; b >= 0; --b) {
                Q[b+D[i].x] = max(Q[b+D[i].x], Q[b]-D[i].y);
            }
        }

        pii ans = {0,0};
        for (int i = 1; i <= B; ++i) {
            ans = max(ans, {Q[i],-i});
        }

        cout << ans.x << endl << -ans.y << endl;
    }
};
