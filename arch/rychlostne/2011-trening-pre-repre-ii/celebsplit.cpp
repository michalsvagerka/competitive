#include "../l/lib.h"
// #include "../l/mod.h"

class celebsplit {
public:
    unordered_map<int,int> F,S;

    void fill(const vector<int> &V, unordered_map<int,int> &Z, int i, int N, int sum, int diff) {
        if (i == N) {
            Z[diff] = max(Z[diff], sum);
            return;
        }

        fill(V, Z, i+1, N, sum, diff);
        fill(V, Z, i+1, N, sum+V[i], diff+V[i]);
        fill(V, Z, i+1, N, sum+V[i], diff-V[i]);
    }


    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        while (N) {
            vector<int> A(N); cin >> A;
            F.clear(); S.clear();
            fill(A, F, 0, N/2, 0, 0);
            fill(A, S, N/2, N, 0, 0);

            int ans = 0;
            for (pii f: F) {
                auto it = S.find(-f.x);
                if (it != S.end()) {
                    ans = max(ans, f.y + it->y);
                }
            }

            int tot = 0;
            for (int a:A) tot += a;
            cout << tot - ans << '\n';

            cin >> N;
        }
    }
};
