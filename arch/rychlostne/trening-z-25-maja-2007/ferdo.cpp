#include "../../../l/lib.h"
// #include "../l/mod.h"

class ferdo {
public:
    void solve(istream& cin, ostream& cout) {
        int T;
        cin >> T;
        for (int t = 1; t <= T; ++t) {
            ll N,M,F,O; cin >> N >> M >> F >> O;
            vector<vector<pii>> Z(N);
            vector<pii> S;
            for (int i = 0; i < N-1; ++i) {
                int c; cin >> c;
                for (int j = 0; j < c; ++j) {
                    int g; cin >> g;
                    if (cin.peek() == '*') {
                        char z; cin >> z;
                        S.emplace_back(i, g);
                    }
                    Z[i+1].emplace_back(g,-1);
                    Z[i].emplace_back(g,1);
                }
            }

            for (int i = 0; i < N; ++i) {
                sort(Z[i].begin(),Z[i].end());
            }

            int tot = 0;
            map<pii,int> I;
            for (int i = 0; i < N; ++i) {
                for (pii z:Z[i]) {
//                    cout << tot << " = " << i << ' ' << z.x << endl;
                    I[{i,z.x}] = tot++;
                }
            }

            vector<vector<pii>> E(tot);
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < Z[i].size(); ++j) {
                    int k = I[{i, Z[i][j].x}];
                    E[k].emplace_back(I[{i + Z[i][j].y, Z[i][j].x}], 1);
                    if (j != 0) E[k].emplace_back(I[{i, Z[i][j-1].x}], Z[i][j].x - Z[i][j-1].x);
                    if (j != Z[i].size() - 1) E[k].emplace_back(I[{i, Z[i][j+1].x}], Z[i][j+1].x - Z[i][j].x);
                }
            }

            minheap<pair<ll,int>> Q;
            vector<ll> D(tot, 1e9);
            for (pii s:S) {
                int f = I[s];
                D[f] = 0;
                Q.push({0,f});
            }
            while (!Q.empty()) {
                auto q = Q.top(); Q.pop();
                if (D[q.y] != q.x) continue;
//                cout << "Fire at " << q.y << " time " << q.x << endl;
                for (pii e: E[q.y]) {
                    if (D[e.x] > q.x + e.y) {
                        D[e.x] = q.x + e.y;
                        Q.push({D[e.x], e.x});
                    }
                }
            }

            vector<ll> W(tot, 1e9);
            W[tot-1] = M - Z.back().back().x;
            Q.push({W[tot-1], tot-1});

            while (!Q.empty()) {
                auto q = Q.top(); Q.pop();
                if (W[q.y] != q.x) continue;
//                cout << "Ferda at " << q.y << " time " << q.x << endl;
                if (O * W[q.y] >= F * D[q.y]) {
//                    cout << "Too late\n";
                    continue;
                }
                for (pii e: E[q.y]) {
                    if (W[e.x] > q.x + e.y) {
                        W[e.x] = q.x + e.y;
                        Q.push({W[e.x], e.x});
                    }
                }
            }

//            cerr << D << W;

            bool isOk = O * W[0] < F * D[0];
            isOk &= O * (W[0] + Z.front().front().x) < F * (D[0] + Z.front().front().x);
            cout << "Zadanie " << t << ": " << (isOk ? "stihne" : "zhori") << "\n";
        }
    }
};
