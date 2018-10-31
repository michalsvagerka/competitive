#include "../l/lib.h"
 #include "../l/graph.h"

class TaskF {
public:
    void solve(istream& cin, ostream& cout) {
        int N;
        cin >> N;
        vector<pii> P(N);
        cin >> P;
        set<int> CX, CY;
        for (int i = 0; i < N; ++i) {
            CX.insert(P[i].x);
            CY.insert(P[i].y);
        }

        map<int, int> CMPX, CMPY;
        vector<int> BX, BY;
        for (int c : CX) {
            CMPX[c] = BX.size();
            BX.push_back(c);
        }
        for (int c : CY) {
            CMPY[c] = BY.size();
            BY.push_back(c);
        }

        for (int i = 0; i < N; ++i) P[i] = {CMPX[P[i].x], CMPY[P[i].y]};
        vector<pair<pii, pii>> Blue, Red;

        int MX = BX.size(), MY = BY.size();
        vector2<bool> S(MX, MY, true);
        for (pii p: P) S[p.x][p.y] = false;

        vector<pair<pii, pii>> Horiz, Vert;
        for (int i = 0; i < MX; ++i) {
            int j = 0;
            while (j < MY && S[i][j]) ++j;
            while (j < MY) {
                while (j < MY && !S[i][j]) ++j;
                if (j < MY) {
                    int k = j;
                    while (j < MY && S[i][j]) ++j;
                    if (j != MY) Horiz.push_back({{i, k}, {i, j - 1}});
                }
            }
        }

        for (int i = 0; i < MY; ++i) {
            int j = 0;
            while (j < MX && S[j][i]) ++j;
            while (j < MX) {
                while (j < MX && !S[j][i]) ++j;
                if (j < MX) {
                    int k = j;
                    while (j < MX && S[j][i]) ++j;
                    if (j != MX) Vert.push_back({{k, i}, {j - 1, i}});
                }
            }
        }

        Bipartite G(Horiz.size(), Vert.size());
        for (int i = 0; i < Horiz.size(); ++i) {
            for (int j = 0; j < Vert.size(); ++j) {
                if (Horiz[i].x.x >= Vert[j].x.x && Horiz[i].x.x <= Vert[j].y.x && Vert[j].x.y >= Horiz[i].x.y && Vert[j].x.y <= Horiz[i].y.y) {
                    G.addEdge(i, Horiz.size()+j);
                }
            }
        }

        G.calcMatching();
        vector<int> Cover = G.cover();
        vector<vector<pii>> RemX(MX), RemY(MY);
        for (int i : Cover) {
            if (i < Horiz.size()) {
                RemX[Horiz[i].x.x].push_back({Horiz[i].x.y,Horiz[i].y.y});
            } else {
                i -= Horiz.size();
                RemY[Vert[i].x.y].push_back({Vert[i].x.x,Vert[i].y.x});
            }
        }

        vector<int> LOX(MY, MX), HIX(MY, 0), LOY(MX, MY), HIY(MX, 0);
        for (pii p:P) {
            LOX[p.y] = min(LOX[p.y], p.x);
            HIX[p.y] = max(HIX[p.y], p.x);
            LOY[p.x] = min(LOY[p.x], p.y);
            HIY[p.x] = max(HIY[p.x], p.y);
        }

        for (int i = 0; i < MX; ++i) {
            int l = LOY[i], r = HIY[i];
            if (RemX[i].empty()) {
                Red.push_back({{i,l},{i,r}});
            } else {
                for (int j = 0; j < RemX[i].size()-1; ++j) {
                    Red.push_back({{i,RemX[i][j].y+1}, {i,RemX[i][j+1].x-1}});
                }
                Red.push_back({{i,l},{i,RemX[i][0].x-1}});
                Red.push_back({{i,RemX[i].back().y+1},{i,r}});
            }
        }

        for (int i = 0; i < MY; ++i) {
            int l = LOX[i], r = HIX[i];
            if (RemY[i].empty()) {
                Blue.push_back({{l,i},{r,i}});
            } else {
                for (int j = 0; j < RemY[i].size()-1; ++j) {
                    Blue.push_back({{RemY[i][j].y+1,i}, {RemY[i][j+1].x-1,i}});
                }
                Blue.push_back({{l,i},{RemY[i][0].x-1,i}});
                Blue.push_back({{RemY[i].back().y+1,i},{r,i}});
            }
        }

        cout << Blue.size() << '\n';
        for (auto b:Blue) cout << BX[b.x.x] << ' ' << BY[b.x.y] << ' ' << BX[b.y.x] << ' ' << BY[b.y.y] << '\n';
        cout << Red.size() << '\n';
        for (auto b:Red) cout << BX[b.x.x] << ' ' << BY[b.x.y] << ' ' << BX[b.y.x] << ' ' << BY[b.y.y] << '\n';
    }
};
