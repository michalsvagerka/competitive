#include "../l/lib.h"

class DAddAndRemove {
public:
    set<vector<int>> Opts;

    ll brute(const vector<int> &W) {
        int M = W.size();
        if (M == 2) {
            return W[0] + W[1];
        } else {
            ll lo = 1e18;
            for (int i = 1; i < M-1; ++i) {
                vector<int> V;
                for (int j = 0; j < M; ++j) {
                    if (j != i) V.push_back(W[j]);
                }
                V[i-1] += W[i];
                V[i] += W[i];
                lo = min(lo, brute(V));
            }
            return lo;
        }
    }

    vector<int> A;
    
    vector<vector<unordered_map<pair<int,int>, ll>>> C;
    int mx = 0;
    
    ll smallest(int l, int r, int a, int b) {
        if (l > r) return 0;
        mx = max(mx, max(a, b));
        auto it = C[l][r].find({a,b});
        if (it != C[l][r].end()) return it->y;
        ll best = 1e18;
        for (int i = l; i <= r; ++i) {
            ll cur = (a+b)*A[i] + smallest(l, i-1, a, (a+b)) + smallest(i+1, r, (a+b), b);
            best = min(best, cur);
        }
        return C[l][r][{a,b}] = best;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        A.resize(N);
        cin >> A;
        C = vector2<unordered_map<pair<int,int>,ll>>(N, N);
        cout << smallest(1, N-2, 1, 1) + A[0] + A[N-1] << '\n';
        cout << mx << endl;
    }
};
