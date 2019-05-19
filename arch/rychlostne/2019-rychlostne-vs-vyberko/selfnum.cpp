#include "../l/lib.h"

class selfnum {
public:

    set<ll> All;

    ll gen(int i, int f, int tot, int sum, vector<int>&c, vector<int>&h) {
        if (i == 10) {
            if (tot == 0) return 0;
            if (c == h) {
                vector<string> W;
                for (int j = 0; j < 10; ++j) {
                    if (c[j] > 0) {
                        stringstream ss;
                        ss << c[j] << j;
                        W.push_back(ss.str());
                    };
                }

                sort(W.begin(),W.end());
                do {
                    string T;
                    for (string w: W) T += w;
                    stringstream TT(T);
                    ll X; TT >> X;
                    All.insert(X);
                } while (next_permutation(W.begin(),W.end()));
                return 1;
            }

            return 0;
        }

        ll ans = gen(i+1, f, tot, sum, c, h);
        if (i != f) {
            for (int k = 1; k <= 11; ++k) {
                tot++;
                sum += i;
                if (tot > 19) {
                    continue;
                }
                if (k < 10) h[k]++;
                if (k == 10) {
                    h[0]++;
                    h[1]++;
                }
                if (k == 11) h[1] += 2;
                h[i]++;

                bool ok = true;
                c[i] = k;
                for (int j = 0; j <= i; ++j) {
                    ok &= c[i] >= h[i];
                }

                if (ok) {
                    ans += gen(i + 1, f, tot, sum, c, h);
                }
                c[i] = 0;

                if (k < 10) h[k]--;
                if (k == 10) {
                    h[0]--;
                    h[1]--;
                }
                if (k == 11) h[1] -= 2;
                h[i]--;
            }
        }
        return ans;
    }

    void solve(istream& cin, ostream& cout) {
        int F, N; cin >> N >> F;

        vector<int> C(10, 0), H(10, 0);
        gen(0, F, 0, 0, C, H);
        for (ll a: All) {
            if (!--N) {
                cout << a << '\n';
                return;
            }
        }
    }
};
