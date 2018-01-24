#include "../l/lib.h"
// #include "../l/mod.h"

class hypercube {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int t = 1;
        while (N) {
            string A,B; cin >> A >> B;
            vector<int> C(N); cin >> C;
            multiset<int> on;
            multiset<int, greater<int>> off;
            multiset<int, greater<int>> perm;
            ll tot = 0;
            for (int i = 0; i < N; ++i) {
                if (A[i] == '1') {
                    tot += C[i];
                    (B[i] == '1' ? perm : off).insert(C[i]);
                } else if (B[i] == '1') on.insert(C[i]);
            }

            ll ans = 0, cur = tot;
            for (int o: off) ans += cur -= o;
            for (int o: on) ans += cur += o;
            ll brute = ans;

            for (int p: perm) {
                on.insert(p);
                off.insert(p);
                cur = tot;
                ans = 0;
                for (int o: off) ans += cur -= o;
                for (int o: on) ans += cur += o;
                brute = min(brute, ans);
            }

            cout << "Case " << t << ": " << brute << '\n';
            ++t;

            cin >> N;
        }

    }
};
