#include "../l/lib.h"
// #include "../l/mod.h"

class plagaty {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        stack<int> S;
        int ans = 0;
        for (int i = 0; i < N; ++i) {
            int w,h; cin >> w >> h;
            while (!S.empty() && S.top() > h) S.pop();
            if (S.empty() || S.top() < h) { S.push(h); ++ans; }
        }

        cout << ans << endl;
    }
};
