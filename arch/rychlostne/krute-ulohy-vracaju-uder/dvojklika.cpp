#include "../../../l/lib.h"
#include "../../../l/mod.h"

class dvojklika {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;

        vector<int> D(N);
        vector<vector<int>> E(N);
        for (int i = 0; i < M; ++i) {
            int a,b; cin >> a >> b;
            --a; --b;
            E[a].push_back(b);
            E[b].push_back(a);
            D[a]++;
            D[b]++;
        }

        sort(D.begin(),D.end());
        reverse(D.begin(),D.end());
        int r = 0;
        for (int i = 0; i < N; ++i) r += D[i];
        int a = 0, ans = 0, i = 0;
        while (i < N && D[i] >= i) { a+=D[i]; r-=D[i]; ++i; }
        if (a == r + i*(i-1)) {
            ans++;
            if (D[i-1] == i-1) {
                ans += count(D.begin(),D.end(),D[i-1]);
            }
        }
        cout << ans << endl;

    }
};
