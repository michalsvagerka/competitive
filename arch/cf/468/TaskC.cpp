#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
    int N, M;

    vector<int> longestNonDecr(const vector<int> &V) {
        vector<int> Q{0}, R{0};
        for (int i = 0; i < M; ++i) {
            auto it = upper_bound(Q.begin(),Q.end(),V[i]);
            if (it == Q.end()) Q.push_back(V[i]);
            else *it = V[i];
            R.push_back(Q.size()-1);
        }
        return R;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> M;
        vector<int> Z(M+1, 0);
        for (int i = 0; i < N; ++i) {
            int l,r; cin >> l >> r;
            Z[l-1]++;
            Z[r]--;
        }

        for (int i = 0; i < M; ++i) {
            Z[i+1] += Z[i];
        }
        Z.pop_back();
        auto A = longestNonDecr(Z);
        reverse(Z.begin(),Z.end());
        auto B = longestNonDecr(Z);
        reverse(B.begin(),B.end());
        int ans = 0;
        for (int i = 0; i <= M; ++i) {
            ans = max(ans, A[i] + B[i]);
        }
        cout << ans << endl;
    }
};
