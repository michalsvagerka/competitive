#include "../l/lib.h"

class CSumBalance {
public:
    void solve(istream& cin, ostream& cout) {
        int K; cin >> K;
        vector<vector<int>> A(K);
        map<ll, int> C;
        vector<ll> Tot(K, 0);
        ll tot = 0;
        for (int i = 0; i < K; ++i) {
            int n; cin >> n;
            A[i].resize(n); cin >> A[i];
            for (ll a: A[i]) { C[a] = i; Tot[i] += a; }
            tot += Tot[i];
        }

        if (tot % K != 0) { cout << "No\n"; return; }
        ll target = tot / K;
        vector<ll> Diff(K);
        for (int i = 0; i < K; ++i) Diff[i] = target - Tot[i];
        
        vector<int> Sol(1<<K, -1000000002);
        for (int i = 0; i < K; ++i) {
            for (int v : A[i]) {
                int cur = v;
                int j = i, m = 0;
                while (!(m&1<<j)) {
                    m |= 1<<j;
                    cur += Diff[j];
                    auto it = C.find(cur);
                    if (it != C.end()) j = it->y;
                }
                if (cur == v) {
                    Sol[m] = v;
                }
            }
        }

        vector<int> FullSol(1<<K, -1);
        FullSol[0] = 100;
        for (int i = 0; i < (1<<K); ++i) {
            if (FullSol[i] != -1) {
                vector<int> Other{0};
                for (int j = 0; j < K; ++j) {
                    if (i&1<<j) continue;
                    int s = Other.size();
                    for (int k = 0; k < s; ++k) {
                        Other.push_back(Other[k] | 1<<j);
                    }
                }
                for (int o: Other) {
                    if (Sol[o] != -1000000002) {
                        FullSol[o|i] = o;
                    }
                }
            }
        }

        if (FullSol.back() != -1) {
            int full = (1<<K)-1;
            vector<int> Take(K, -1), To(K, -1);
            while (full) {
                int back = FullSol[full];
                int cur = Sol[back];
                for (int i = 0; i < K; ++i) {
                    int j = C[cur];
                    Take[j] = cur;
                    cur += Diff[j];
                    To[C[cur]] = j;
                }

                full ^= back;
            }

            cout << "Yes\n";
            for (int i = 0; i < K; ++i) cout << Take[i] << ' ' << To[i]+1 << '\n';
        } else {
            cout << "No\n";
        }
    }
};
