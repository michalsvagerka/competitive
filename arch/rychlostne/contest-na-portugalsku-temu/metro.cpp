#include "../l/lib.h"
#include "../l/blossom.h"
#include "../l/util.h"

class metro {
public:
    vector<int> shortest(int u, int v, const vector<vector<bool>>&E) {
        int N = E.size();
        vector<int> C(N, N), Q{u}, P(N, -1);
        C[u] = 0;
        for (int q = 0; q < Q.size(); ++q) {
            int w = Q[q];
            for (int i = 0; i < N; ++i) {
                if (E[w][i] && C[i] == N) {
                    C[i] = C[w] + 1;
                    P[i] = w;
                    Q.push_back(i);
                }
            }
        }

        vector<int> Path{v};
        int z = v;
        while (P[z] != -1) { z = P[z]; Path.push_back(z); }
        reverse(Path.begin(),Path.end());
        return Path;
    }

    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector2<bool> A(N, N, true), E(N, N, false);
        vector<int> D(N, 0);
        vector2<int> B(N, N, 1);
        UnionFind UF(N);
        for (int i = 0; i < N; ++i) B[i][i] = 10000;
        for (int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            --a; --b;
            D[a]++; D[b]++;
            UF.unite(a, b);
            A[a][b] = A[b][a] = false;
            E[a][b] = E[b][a] = true;
            B[a][b] = B[b][a] = 10000;
        }

        for (int k = 0; k < N; ++k) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    B[i][j] = min(B[i][j], B[i][k] + B[k][j]);
                }
            }
        }

        vector<int> Odd;
        for (int i = 0; i < N; ++i) if (D[i]%2 == 1) Odd.push_back(i);
        int S = Odd.size();

        Matcher MTCH(S);
        for (int i = 0; i < S; ++i) {
            for (int j = i+1; j < S; ++j) {
                int c = B[Odd[i]][Odd[j]];
                if (c != 10000) MTCH.add_edge(i, j, 100000-c);
            }
        }
        MTCH.get_matching(true);
        
        vector<pii> Add;
        auto toggle = [&](int a, int b) {
            if (a > b) swap(a,b);
            D[a]++; D[b]++;
            
            if (E[a][b]) {
                Add.erase(std::remove(Add.begin(), Add.end(), pii{a,b}), Add.end());
                E[a][b] = E[b][a] = false;
            } else {
                Add.emplace_back(a,b);
                UF.unite(a,b);
                E[a][b] = E[b][a] = true;
            }
        };
        for (int i = 0; i < S; ++i) {
            if (MTCH.mate[i] == -1) {
                cout << "-1\n";
                return;
            }

            if (MTCH.mate[i] > i) {
                auto pp = shortest(Odd[i], Odd[MTCH.mate[i]], A);
                int l = pp.size();
                for (int j = 0; j < l-1; ++j) toggle(pp[j], pp[j+1]);
            }
        }

        while (UF.comp > 1) {
            map<int, pii> Inside;
            bool mod = false;
            for (pii a: Add) {
                Inside[UF.find(a.x)] = a;
                if (Inside.size() >= 2) {
                    pii e = Inside.begin()->y;
                    pii f = next(Inside.begin())->y;
                    toggle(e.x, f.x);
                    toggle(e.y, f.y);
                    toggle(e.x, e.y);
                    toggle(f.x, f.y);
                    mod = true;
                }
            }

            if (mod) continue;

            map<int, int> Comps;
            for (int i = 0; i < N; ++i) Comps[UF.find(i)] = i;

            if (Inside.size() == 1) {
                int c = Inside.begin()->x;
                pii e = Inside.begin()->y;
                vector<int> Other;
                for (pii d: Comps) if (c != d.x) Other.push_back(d.y);
                toggle(e.x, e.y);
                toggle(e.x, Other[0]);
                toggle(e.y, Other.back());
                for (int i = 1; i < Other.size(); ++i) toggle(Other[i], Other[i-1]);
            } else {
                if (Comps.size() == 2) {
                    bool done = false;
                    for (int i = 0; i < N && !done; ++i) {
                        for (int j = i+1; j < N && !done; ++j) {
                            if (UF.united(i, j) && !E[i][j]) {
                                for (int k = 0; k < N && !done; ++k) {
                                    if (!UF.united(i, k)) {
                                        done = true;
                                        toggle(i, j);
                                        toggle(i, k);
                                        toggle(k, j);
                                    }
                                }
                            }
                        }
                    }

                    if (done) break;

                    map<int, vector<int>> CC;
                    for (int i = 0; i < N; ++i) CC[UF.find(i)].push_back(i);
                    auto a = *CC.begin();
                    auto b = *next(CC.begin());
                    if (a.y.size() == 1 || b.y.size() == 1) {
                        cout << "-1\n";
                        return;
                    }

                    toggle(a.y[0], b.y[0]);
                    toggle(a.y[0], b.y[1]);
                    toggle(a.y[1], b.y[0]);
                    toggle(a.y[1], b.y[1]);
                } else {
                    vector<int> All;
                    for (pii d: Comps) All.push_back(d.y);
                    for (int i = 1; i < All.size(); ++i) toggle(All[i], All[i-1]);
                    toggle(All[0], All.back());
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            if (D[i]%2==1) {
                cout << "-1\n";
                return;
            }
        }
        
        cout << Add.size() << '\n';
        for (pii a: Add) cout << a.x + 1 << ' ' << a.y + 1 << endl;
    }
};
