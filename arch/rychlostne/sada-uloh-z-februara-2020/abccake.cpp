#include "../l/lib.h"

class abccake {
public:
    void solve(istream& cin, ostream& cout) {
        int A, B, C; cin >> A >> B >> C;
        int tot = A*B*C;
        vector<int> S{B*C, A*C, A*B}, T{1,1,1}, L = S;
        vector<vector<int>> Sol;
        while (T[0] <= A) {
            int u = *min_element(L.begin(),L.end());
            Sol.push_back({u, T[0], T[1], T[2]});
            for (int i = 0; i < 3; ++i) {
                L[i] -= u;
                if (L[i] == 0) {
                    T[i]++;
                    L[i] = S[i];
                }
            }
        }

        cout << Sol.size() << '\n';
        for (auto &s: Sol) cout << s;
    }
};
