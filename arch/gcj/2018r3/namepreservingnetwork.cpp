#include "../../../l/lib.h"
 #include "../../../l/random.h"

class namepreservingnetwork {
public:
    vector<vector<int>> E, F;

    void fooGen(int N) {
        int time = 0;
        while (true) {
            time++;
            E.clear(); E.resize(N);

            auto hasEdge = [&](int i, int j) { return count(E[i].begin(),E[i].end(),j) != 0; };

            bool fail = false;
            for (int i = 0; i < N-1; ++i) {
                while (E[i].size() < 4) {
                    random_int RR(i+1, N-1);
                    int j = i;
                    int att = 0;
                    while (i == j || E[j].size() == 4 || hasEdge(i,j)) {
                        j = RR(rng);
                        if (att++ > 5+2*(N-i)) { fail = true; break; }
                    }
                    E[i].push_back(j);
                    E[j].push_back(i);
                    if (fail) break;
                }
                if (fail) break;
            }
            if (fail || E[N-1].size() != 4) continue;
            auto K = assign(N, E, E);
            if (count(K.begin(),K.end(),-1) == 0) {
                cerr << time << ' ';
                return;
            }
        }

    }

    vector<int> assign(int N, vector<vector<int>> &E, vector<vector<int>> &F) {
        vector<int> T1(N,0), T2(N,0), F1(N,0), F2(N,0);
        trif(N, E, T1, F1);
        trif(N, F, T2, F2);

        vector<int> K(N, -1), R(N, -1);
        for (int i = 0; i < N; ++i) {
            bool fail = false;
            for (int j = 0; j < N; ++j) fail |= (i!=j && T1[i] == T1[j] && F1[j] == F1[i]);
            if (!fail) for (int k = 0; k < N; ++k) if (T2[k] == T1[i] && F2[k] == F1[i]) { K[i] = k; R[k] = i; }
        }

        int ch = 0;
        while (!ch++) {
            vector<set<int>> FORW(N), BACKW(N);
            for (int i = 0; i < N; ++i) {
                if (K[i] == -1) for (int j : E[i]) if (K[j] != -1) FORW[i].insert(j);
            }

            for (int i = 0; i < N; ++i) {
                if (R[i] == -1) for (int j : F[i]) if (R[j] != -1) BACKW[i].insert(R[j]);
            }

            for (int i = 0; i < N; ++i) {
                if (K[i] != -1) continue;
                bool fail = false;
                for (int j = 0; j < N; ++j) {
                    fail |= (i != j && K[j] == -1 && FORW[i] == FORW[j]);
                }
                if (!fail) {
                    for (int j = 0; j < N; ++j) {
                        if (R[j] == -1 && BACKW[j] == FORW[i]) { K[i] = j; R[j] = i; ch = 0; }
                    }
                }
            }
        }
        return K;
    }

    void trif(int N, vector<vector<int>> &W, vector<int> &T, vector<int> &F) {
        auto hasEdge = [&](int i, int j) { return count(W[i].begin(),W[i].end(),j) != 0; };

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    if (i != j && j != k && k != i && hasEdge(i,j) && hasEdge(j,k) && hasEdge(k,i)) {
                        T[i]++; T[j]++; T[k]++;
                    }
                }
            }
        }


        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    for (int l = 0; l < N; ++l) {
                        if (i != j && i != k && i != l && j != l && j != k && k != l &&hasEdge(i, j) && hasEdge(j, k) && hasEdge(k, l) && hasEdge(l, i)) {
                            F[i]++; F[j]++; F[k]++; F[l]++;
                        }
                    }
                }
            }
        }
    }

    void gen(int N) {
        E.clear();
        E.resize(N);
        vector<int> C;

        for (int i = 0; i < N; ++i) {
            if (i != 0 && i != 2 && i != 5) {
                C.push_back(i);
            }
        }

        for (int i = 0; i < N; ++i) {
            E[i].push_back((i + 1) % N);
            E[(i + 1) % N].push_back(i);
        }

        E[0].push_back(2);
        E[0].push_back(5);
        E[2].push_back(0);
        E[2].push_back(5);
        E[5].push_back(0);
        E[5].push_back(2);

        for (int i = 0; i < C.size(); ++i) {
            E[C[i]].push_back(C[(i + 3) % C.size()]);
            E[C[(i + 3) % C.size()]].push_back(C[i]);
        }
    }


    void solve(istream& cin, ostream& cout) {
        ui T; cin >> T;
        for (int t = 1; t <= T; ++t) {
            int L, U; cin >> L;
            if (L == -1) break;
            cin >> U;
            int N = L;
            fooGen(N);
            cout << N << '\n';
            for (int i = 0; i < N; ++i) {
                for (int j : E[i]) {
                    if (j > i) {
                        cout << i+1 << ' ' << j+1 << '\n';
                    }
                }
            }
            flush(cout);

            int M; cin >> M;
            F.clear(); F.resize(N);
            for (int i = 0; i < 2*N; ++i) {
                int u, v;
                cin >> u >> v;
                --u;
                --v;
                F[u].push_back(v);
                F[v].push_back(u);
            }


            auto K = assign(N, E, F);
            for (int&k:K) ++k;
            cout << K;
            flush(cout);
        }
    }
};
