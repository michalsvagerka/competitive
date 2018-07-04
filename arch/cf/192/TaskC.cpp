#include "../l/lib.h"
#include <numeric>
#include "../l/random.h"

class TaskC {
public:
    vector<vector<int>> E;
    vector<bool> V;

    void dfs(int u, vector<int> &Q) {
        if (V[u]) return;
        V[u] = true;
        Q.push_back(u);
        for (int v:E[u]) dfs(v, Q);
    }

void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    E.resize(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        E[u].push_back(v);
        E[v].push_back(u);
    }

    if (N <= 10) {
        vector<int> I(N);
        iota(I.begin(),I.end(),0);
        do {
            bool ok = true;
            for (int k = 0; k < M; ++k) {
                int u = I[k];
                int v = I[(k+1)%N];
                for (int w:E[u]) ok &= w != v;
            }

            if (ok) {
                for (int k = 0; k < M; ++k) {
                    int u = I[k];
                    int v = I[(k + 1) % N];
                    cout << u + 1 << ' ' << v + 1 << '\n';
                }
                return;
            }
        } while (next_permutation(I.begin(),I.end()));

        cout << "-1\n";
    } else {
        V = vector<bool>(N, false);
        vector<vector<int>> Q;
        for (int i = 0; i < N; ++i) {
            if (!V[i] && E[i].size() == 1) {
                Q.push_back({});
                dfs(i, Q.back());
            }
        }

        for (int i = 0; i < N; ++i) {
            if (!V[i] && E[i].size() == 2) {
                Q.push_back({});
                dfs(i, Q.back());
            }
        }

        sort(Q.begin(),Q.end(),[&](const vector<int>&v, const vector<int>&w) {
            return v.size() == 3 && w.size() != 3;
        });

        vector<vector<int>> A(3);
        int h = 0;
        for (auto &q : Q) {
            if (q.size() == 2) {
                A[h%3].push_back(q[0]);
                h++;
                A[h%3].push_back(q[1]);
            } else if (q.size() == 3) {
                A[0].push_back(q[0]);
                A[1].push_back(q[1]);
                A[2].push_back(q[2]);
            } else if (q.size() == 4) {
                A[0].push_back(q[1]);
                A[0].push_back(q[3]);
                A[1].push_back(q[0]);
                A[2].push_back(q[2]);
            } else if (q.size() == 5) {
                A[0].push_back(q[0]);
                A[0].push_back(q[3]);
                A[1].push_back(q[1]);
                A[1].push_back(q[4]);
                A[2].push_back(q[2]);
            } else if (q.size() == 6) {
                A[0].push_back(q[1]);
                A[0].push_back(q[4]);
                A[1].push_back(q[2]);
                A[1].push_back(q[0]);
                A[2].push_back(q[3]);
                A[2].push_back(q[5]);
            } else {
                for (int i = 0; i < q.size(); i += 3) {
                    A[0].push_back(q[i]);
                }
                for (int i = 1; i < q.size(); i += 3) {
                    A[1].push_back(q[i]);
                }

                for (int i = 2; i < q.size(); i += 3) {
                    A[2].push_back(q[i]);
                }

                int z = A[2].size();
                swap(A[2][z-2], A[2][z-1]);
            }
        }

        int j = 0;
        for (int i = 0; i < N; ++i) {
            if (E[i].empty()) {
                A[j%3].push_back(i);
                j++;
            }
        }

        vector<int> B;

        for (auto&a:A) for (int aa:a) B.push_back(aa);
        if (B.size() < N) {
            cout << B.size() << ' ' << N << endl;
            return;
        }

//        do {
            bool ok = true;
            for (int k = 0; k < M && ok; ++k) {
                int u = B[k];
                int v = B[(k + 1) % N];
                for (int w:E[u]) ok &= w != v;
            }

            if (ok) {
                for (int k = 0; k < M; ++k) {
                    int u = B[k];
                    int v = B[(k + 1) % N];
                    cout << u + 1 << ' ' << v + 1 << '\n';
                }
                return;
            }

//            shuffle(B.begin(),B.end(),rng);
//        } while (true);
    }

}
};
