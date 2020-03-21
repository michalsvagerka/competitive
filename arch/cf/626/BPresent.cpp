#include "../l/lib.h"

constexpr int MX = 25;
class BPresent {
public:
    void solve(istream& cin, ostream& cout) {
        int N;
        cin >> N;
        vector<int> A(N);
        cin >> A;


        ll ans = 0;


        for (int i = 0; i < MX; ++i) {
            vector<vector<int>> Cnt(MX);
            for (int j = i; j < MX; ++j) {
                Cnt[j].assign(1<<(j-i+1), 0);
            }
            for (int a: A) {

                for (int j = i; j < MX; ++j) {
                    int m = ((1 << (j - i + 1)) - 1);
                    int h = (a >> i) & m;
                    if (i==0) {
                        int other = h^m;
                        if (Cnt[j][other]&1) {
                            ans ^= 1<<j;
                        }
                    }

                    if (((h&1)==0) && i!=j) {
                        int other = h^m^1;
                        if (Cnt[j][other]&1) {
                            ans ^= 1<<j;
                        }
                    }

                    if ((h&1)==1 && i != j) {
                        int other = h^m^1^(1<<(j-i));
                        if (Cnt[j][other]&1) {
                            ans ^= 1<<j;
                        }
                    }

                    Cnt[j][h]++;
                }
            }
        }

//        for (int i = 0; i < MX; ++i) {
//            for (int j = i; j < MX; ++j) {
//                if (j != i) {
//                    int q = 1<<(j-i-1);
//                    int w = 1<<(j-i)
//                    ll cur = 0;
//                    for (int b = 0; b < q; ++b) {
//                        cur += ll(Cnt[i][j][(b<<1)|1])*ll(Cnt[i][j][(b<<1)|1]);
//                        cur += ll(Cnt[i][j][w|(b<<1)|1])*ll(Cnt[i][j][(w|(b<<1)|1]);
//                    }
//                    cur /= 2;
//                    if (cur&1) ans ^= 1<<j;
//                }
//            }
//        }


//        for (int a: A) ans ^= 2*a;

        cout << ans << '\n';
    }
};
