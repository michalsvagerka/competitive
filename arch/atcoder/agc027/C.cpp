#include "../l/lib.h"
// #include "../l/mod.h"

class C {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    string S; cin >> S;
    vector<vector<int>> E(N);
    for (int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        --a; --b;
        E[a].push_back(b);
        E[b].push_back(a);
    }

    vector<bool> Good(N, true);
    vector<int> GoodA(N, 0), GoodB(N, 0);
    vector<int> Bad;
    for (int i = 0; i < N; ++i) {
        for (int j : E[i]) {
            if (S[j] == 'A') {
                GoodA[i]++;
            } else GoodB[i]++;
        }
        if (!GoodA[i] || !GoodB[i]) Bad.push_back(i);
    }

    for (int i = 0; i < Bad.size(); ++i) {
        int u = Bad[i];
        Good[u] = false;
        for (int v : E[u]) {
            if (Good[v]) {
                if (S[u]=='A') {
                    if (!--GoodA[v] && GoodB[v]) Bad.push_back(v);
                } else {
                    if (!--GoodB[v] && GoodA[v]) Bad.push_back(v);
                }
            }
        }
    }

    cout << (Bad.size() == N ? "No" : "Yes") << endl;
}
};
