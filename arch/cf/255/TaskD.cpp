#include "../l/lib.h"
 #include "../l/matrix.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int N, M, K; cin >> N >> M >> K;
    vector<vector<int>> E(N);
    vector<int> T(N); cin >> T;
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        E[u].push_back(v);
        E[v].push_back(u);
    }

    vector2<double> D(N, N, 0);
    for (int u = 0; u < N; ++u) {
        for (int v:E[u]) {
            D[u][v] += 1.0/E[u].size();
        }
    }

    auto relax = [&](int v) {
        if (D[v][v] > 1e-10) {
            for (int w = 0; w < N; ++w) {
                if (v != w) {
                    D[v][w] /= (1 - D[v][v]);
                }
            }
            D[v][v] = 0;
        }


        for (int u = 0; u < N; ++u) {
            if (u != v && D[u][v] > 1e-10) {
                for (int w = 0; w < N; ++w) {
                    if (w != v && D[v][w] > 1e-10) {
                        D[u][w] += D[u][v] * D[v][w];
                    }
                }
            }
        }

        for (int u = 0; u < N; ++u) {
            D[u][v] = 0;
            D[v][u] = 0;
        }
    };
    for (int v = 0; v < N; ++v) {
        if (v != 0 && !T[v]) {
            relax(v);
        }
    }


    vector<double> Init;
    for (int u = 0; u < N; ++u) {
        if (T[u]) {
            Init.push_back(D[0][u] / (1-D[0][0]));
        }
    }

    vector<vector<double>> Trans;
    relax(0);
    for (int u = 0; u < N; ++u) {
        if (T[u]) {
            Trans.push_back({});
            for (int v = 0; v < N; ++v) {
                if (T[v]) {
                    Trans.back().push_back(D[u][v]);
                }
            }
        }
    }

    Matrix<double> A(Trans);
    auto L = A.power(K-2).transpose() * Init;
    cout << fixed << setprecision(10) << L.back() << endl;

}
};
