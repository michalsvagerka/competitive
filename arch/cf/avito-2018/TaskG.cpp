#include "../l/lib.h"
#include "../l/runtimemod.h"

class TaskG {
public:
    int Q;

    vector<int> mergeSort(const vector<int>&a, int l, int r, int h) {
        vector<int> b;
        if (l <= r) {
            if (h <= 1) {
                for (int i = l; i <= r; ++i) b.push_back(a[i-1]);
            } else {
                int m = (l+r)/2;
                auto c = mergeSort(a, l, m, h-1);
                auto d = mergeSort(a, m+1, r, h-1);
                int i = 0, j = 0;
                while (i != c.size() || j != d.size()) {
                    if (i == c.size()) {
                        b.push_back(d[j++]);
                    } else if (j == d.size()) {
                        b.push_back(c[i++]);
                    } else if (c[i] < d[j]) {
                        b.push_back(c[i++]);
                    } else {
                        b.push_back(d[j++]);
                    }
                }
            }
        }
        return b;
    }

    map<int, int> BLK;

    void solve(int L, int K) {
        if (L == 1 || K == 1) {
            BLK[L]++;
        } else {
            solve(L/2, K-1);
            solve((L+1)/2, K-1);
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K >> Q;
        RField ans{0,Q};
        solve(N, K);
        vector<RField> Pref(2*N+1, RField{0,Q});
        for (int i = 1; i <= 2*N; ++i) {
            Pref[i] = Pref[i-1] + RField{1,Q}/i;
        }

        for (pii a : BLK) {
            for (pii b : BLK) {
                RField cur{0,Q};
                for (int i = 1; i <= a.x; ++i) cur -= Pref[i+b.x] - Pref[i];
                cur += RField{a.x, Q} * RField{b.x, Q} / 2;
                if (a.x < b.x) {
                    ans += cur * a.y * b.y;
                } else if (a.x == b.x) {
                    ans += cur * a.y * (a.y-1) / 2;
                }
            }

            ans += RField{a.x,Q}*RField{a.x-1,Q}*a.y/4;
        }
        cout << ans << '\n';

    }
};
