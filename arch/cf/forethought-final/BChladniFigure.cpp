#include "../l/lib.h"

class BChladniFigure {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<vector<int>> E(N);
        for (int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            --a; --b;
            if (b < a) b += N;
            int d = b - a;
            E[d].push_back(a);
            E[N-d].push_back(b%N);
        }

        vector<int> F;
        for (int i = 0; i < N; ++i) {
            if (!E[i].empty()) {
                F.push_back(i);
                sort(E[i].begin(),E[i].end());
            }
        }

        for (int i = 1; i < N; ++i) {
            if (N%i == 0) {
                bool ok = true;
                for (int j : F) {
                    vector<int> S, T;
                    for (int b: E[j]) {
                        if (b + i < N) S.push_back(b+i);
                        else T.push_back((b+i)%N);
                    }
                    for (int s: S) T.push_back(s);
                    if (T != E[j]) { ok = false; break; }
                }
                if (ok) {
                    cout << "Yes\n";
                    return;
                }
            }
        }
        cout << "No\n";
    }
};
