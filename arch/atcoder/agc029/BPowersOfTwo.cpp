#include "../l/lib.h"
// #include "../l/mod.h"

class BPowersOfTwo {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        multiset<int> M;
        for (int a:A) M.insert(a);
        int ans = 0;
        while (!M.empty()) {
            auto it = prev(M.end());
            int v = *it;
            M.erase(it);

            int x = 1;
            while (x <= v) x *= 2;
            auto it2 = M.find(x-v);
            if (it2 != M.end()) {
                M.erase(it2);
                ++ans;
            }
        }

        cout << ans << '\n';
    }
};
