#include "../l/lib.h"

class EsabAtad {
public:
    void solve(istream& cin, ostream& cout) {
        int T, B; cin >> T >> B;
        for (int t = 0; t < T; ++t) {
            vector<int> Ans(B, -1);
            bool fail = false;
            auto query = [&](int i) {
                cout << i+1 << endl;
                char a; cin >> a;
                if (a == 'N') {
                    fail = true;
                }
                return a-'0';
            };

            int diff = -1, same = -1;
            for (int i = 0; i < 5; ++i) {
                Ans[i] = query(i); if (fail) return;
                Ans[B-i-1] = query(B-i-1); if (fail) return;
                if (Ans[i] == Ans[B-i-1]) {
                    same = i;
                } else {
                    diff = i;
                }
            }

            int j = 5;
            while (true) {
                if (j >= B/2) {
                    for (int a: Ans) cout << a;
                    cout << endl;
                    char c; cin >> c;
                    if (c == 'N') return;
                    else break;
                }

                if (same != -1) {
                    int q = query(same); if (fail) return;
                    if (Ans[same] != q) {
                        // this has been inverted
                        for (int i = 0; i < B; ++i) if (Ans[i] != -1) Ans[i] = 1 - Ans[i];
                    }
                } else { query(0); if (fail) return; }

                if (diff != -1) {
                    int q = query(diff); if (fail) return;
                    if (Ans[diff] != q) {
                        // this has been reversed
                        reverse(Ans.begin(),Ans.end());
                    }
                } else { query(0); if (fail) return; }

                for (int k = j; k < (min(B/2, j+4)); ++k) {
                    Ans[k] = query(k); if (fail) return;
                    Ans[B-k-1] = query(B-k-1); if (fail) return;
                    if (Ans[k] == Ans[B-k-1]) {
                        same = k;
                    } else {
                        diff = k;
                    }
                }
                j += 4;
            }
        }
    }
};
