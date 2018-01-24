#include "../l/lib.h"
// #include "../l/mod.h"

class outskirts {
public:
    void solve(istream& cin, ostream& cout) {
        int N,r; cin >> N;
        vector<int> D(N);
        for (int i = 0; i < N; ++i) {
            cin >> D[i];
            for (int j = 0; j < D[i]; ++j) {
                cin >> r;
            }
        }
        sort(D.begin(),D.end());
        reverse(D.begin(),D.end());
        r = 0;
        for (int i = 0; i < N; ++i) r += D[i];
        int a = 0, ans = 0, i = 0;
        while (i < N && D[i] >= i) { a+=D[i]; r-=D[i]; ++i; }
        if (a == r + i*(i-1)) {
            if (i < N && D[0] > 0) ans++;
            if (D[i-1] == i-1) {
                ans += count(D.begin(),D.end(),D[i-1]);
            }
        }
        cout << ans << endl;
    }
};
