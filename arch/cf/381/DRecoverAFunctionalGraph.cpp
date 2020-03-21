#include "../l/lib.h"
#include <sstream>
#include "../l/graph.h"

class DRecoverAFunctionalGraph {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> V(N);
        vector2<vector<int>> Full(N+1, N+1);
        vector<vector<int>> Cycle(N+1);
        vector<vector<int>> Precycle(N+1);
        vector<bool> HasCycle(N+1, false);
        vector<int> Free;
        vector<pii> Need;

        for (int i = 0; i < N; ++i) {
            string s; int a;
            cin >> s; if (s == "?") V[i].x = -1; else { stringstream ss(s); ss >> a; V[i].x = a; }
            cin >> s; if (s == "?") V[i].y = -1; else { stringstream ss(s); ss >> a; V[i].y = a; }
            if (V[i].x == -1) {
                if (V[i].y == -1) {
                    Free.push_back(i);
                } else {
                    HasCycle[V[i].y] = true;
                    Cycle[V[i].y].push_back(i);
                }
            } else {
                if (V[i].y == -1) {
                    Precycle[V[i].x].push_back(i);
                } else {

                    HasCycle[V[i].y] = true;
                    Full[V[i].y][V[i].x].push_back(i);
                }
            }
        }

        for (int cyc = 1; cyc <= N; ++cyc) {
            bool has = false;
            for (int prec = N; prec > 0; --prec) {
                if (!Full[cyc][prec].empty()) {
                    has = true;
                } else if (has) {
                    Need.emplace_back(prec, cyc);
                }
            }

            if (has || !Cycle[cyc].empty() || !Full[cyc][0].empty()) {
                int x = Full[cyc][0].size();
                while (x == 0 || x%cyc != 0) {
                    x++;
                    Need.emplace_back(0, cyc);
                }
            }
        }

        int highestPrec = -1;
        for (int prec = N; prec > 0; --prec) {
            if (!Precycle[prec].empty()) {
                highestPrec = max(highestPrec, prec);
            }
        }

        for (int cyc = 1; cyc <= N; ++cyc) {
            vector<pii> Real = Need;
            for (int prec = N; prec >= 0; --prec) {
                if (!Full[cyc][prec].empty()) break;

                if (prec <= highestPrec) {
                    if (prec == 0) {
                        if (!HasCycle[cyc]) {
                            for (int j = 0; j < cyc; ++j) {
                                Real.emplace_back(0, cyc);
                            }
                        }
                    } else {
                        Real.emplace_back(prec, cyc);
                    }
                }
            }

            Bipartite G(N, Real.size());
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < Real.size(); ++j) {
                    if ((V[i].x == -1 || V[i].x == Real[j].x) && (V[i].y == -1 || V[i].y == Real[j].y) && (V[i].x == -1 || V[i].y == -1)) {
                        G.addEdge(i, N + j);
                    }
                }
            }
            G.calcMatching();

            if (G.matchingSize() == Real.size()) {
                auto W = V;
                for (int i = 0; i < N; ++i) {
                    if (G.matched(i) != -1) {
                        W[i] = Real[G.matched(i) - N];
                    } else if (W[i] == pii{-1,-1}) {
                        W[i] = {0,1};
                    } else if (W[i].x == -1) {
                        W[i].x = 1;
                    } else if (W[i].y == -1) {
                        if (W[i].x == 0) {
                            W[i].y = 1;
                        } else {
                            W[i].y = cyc;
                        }
                    }
                }

                vector<int> Par(N, -1);
                vector<vector<int>> Q(N+1);
                for (int i = 0; i < N; ++i) {
                    if (W[i].x > 0) {
                        for (int j = 0; j < N; ++j) {
                            if (W[j].x + 1 == W[i].x && W[j].y == W[i].y) Par[i] = j;
                        }
                    } else {
                        Q[W[i].y].push_back(i);
                    }
                }

                for (int i = 1; i <= N; ++i) {
                    for (int j = 0; j < Q[i].size(); ++j) {
                        Par[Q[i][j]] = j%i==0?Q[i][j+i-1]:Q[i][j-1];
                    }
                }

                for (int &p: Par) ++p;
                cout << Par;
                return;
            }
        }

        cout << -1 << endl;
    }
};
