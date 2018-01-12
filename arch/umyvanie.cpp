#include "../l/lib.h"
// #include "../l/mod.h"

class umyvanie {
public:
    vector<vector<ui>> E;
    ui N;
    vector<ui> S;

    ui size(ui u) {
        ui s = 1;
        for (ui v:E[u]) s+=size(v);
        S[s]++;
        return s;
    }

    ui count(ui c) {
        ui t = 0;
        for (int i = c; i <= N; i+=c) t += S[i];
        return t;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N; E.resize(N);
        for (ui i = 1; i < N; ++i) {
            int a; cin >> a; --a;
            E[a].push_back(i);
        }

        S = vector<ui>(N+1,0);
        size(0);

        cout << 1;
        for (int j = 2; j < N; ++j) {
            if (N % j == 0 && count(N/j) == j) cout << ' ' << j;
        }
        cout << ' ' << N << endl;
    }
};
