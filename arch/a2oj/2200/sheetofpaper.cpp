#include "../l/lib.h"
#include "../l/fenwick.h"

class sheetofpaper {
public:
    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
//        vector<int> W(N, 1);
        Fenwick<int> F(N, 0);
        for (int i = 0; i < N; ++i) F.set(i, 1);

        int L = 0, R = N-1;
        bool swapped = false;
        for (int q = 0; q < Q; ++q) {
            int t; cin >> t;
            if (t == 1) {
                int f; cin >> f;
                if (L+2*f > R) {
                    // no place to fold
                    swapped = !swapped;
                    f = R-L+1-f;
                }

                if (swapped) {
                    for (int i = 0; i < f; ++i) {
                        F.add(R - (2 * f - 1) + i, F.get(R - i));
                        F.add(R-i, -F.get(R - i));
                    }
                    R -= f;
                } else {
                    for (int i = 0; i < f; ++i) {
                        F.add(L + (2 * f - 1) - i, F.get(L+i));
                        F.add(L+i, -F.get(L+i));
                    }
                    L += f;
                }
            } else if (t == 2) {
                int l, r; cin >> l >> r;
                --r;
                if (swapped) {
                    l = R-l;
                    r = R-r;
                    swap(l,r);
                } else {
                    l += L;
                    r += L;
                }
                cout << F.range(l,r) << '\n';
            }
        }

    }
};
