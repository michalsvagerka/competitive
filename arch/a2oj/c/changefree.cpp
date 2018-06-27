#include "../../../l/lib.h"
// #include "../l/mod.h"

class changefree {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> C(N), W(N); cin >> C >> W;
        vector<bool> CH(N, false);
        minheap<pii> H;
        ll ans = 0;
        for (int i = 0; i < N; ++i) {
            int c = C[i]%100;
            M -= c;
            if (c) H.push({W[i]*(100-c),i});
            if (M < 0) {
                ans += H.top().x;
                CH[H.top().y] = true;
                H.pop();
                M += 100;
            }
        }

        cout << ans << '\n';
        for (int i = 0; i < N; ++i) {
            if (CH[i]) {
                cout << C[i]/100 + 1 << " 0\n";
            } else {
                cout << C[i]/100 << ' ' << C[i]%100 << '\n';
            }
        }

    }
};
