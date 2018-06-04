#include "../l/lib.h"
#include "../l/mod.h"
#include "../l/suffixarray.h"

class tavasandmalekas {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        string P; cin >> P;
        int R = P.size();
        P += '$';
        SuffixArray<int, true, true> SA(P);
        int rep = N;
        for (int i = 1; i < R; ++i) {
            if (SA.lcp(0, i) == R-i) {
                rep = i;
                break;
            }
        }

        vector<bool> occurs(N, false);
        for (int i = 0; i < M; ++i) {
            int q; cin >> q; occurs[q-1] = true;
        }

        int p = 0;
        for (int i = 0; i < N;) {
            if (occurs[i]) {
                for (int j = i; j < min(N, i+R); j++) {
                    if (occurs[j]) {
                        if ((j-i)%rep == 0) {
                            i = j;
                        } else {
                            cout << "0\n";
                            return;
                        }
                    }
                }

                i += R;
            } else {
                ++p;
                ++i;
            }
        }

        cout << FieldMod{26}.pow(p) << '\n';
    }
};
