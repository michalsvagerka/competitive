#include "../../../l/lib.h"
// #include "../l/mod.h"

class C {
public:
    void solve(istream& cin, ostream& cout) {
        int N, X; cin >> N >> X;
        vector<int> Q(N);
        cin >> Q;
        sort(Q.begin(),Q.end());
        ll tot = 0;
        ll stay = 0;
        for (int q:Q) tot += q;
        int bot = (tot+X-1) / X;
        vector<int> B(bot);
        for (int i = 0; i < bot; ++i) {
            B[i] = X - Q[N - 1 - i];
            stay += Q[N - 1 - i];
        }
        sort(B.begin(),B.end());
        for (int i = bot-1; i > 0; --i) B[i] -= B[i-1];

        int ans = 0;
        ll spend = tot - stay;
        for (int i = 0; i < bot; ++i) {
            ll cur = spend/(bot-i);
            if (cur > B[i]) cur = B[i];

            ans += cur;
            spend -= cur*(bot-i);
            if (cur < B[i] && spend > 0 && spend < bot-i) {
                ans++;
                spend = 0;
            }
        }

        for (int i = 0; i < N-bot; ++i) ans = max(ans, Q[i]);

        cout << bot << ' ' << ans << endl;

    }
};
