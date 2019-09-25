#include "../l/lib.h"

class CLuckyTickets {
public:
    vector<int> X;

    set<int> run(int i, int j) {
        int a = 0;
        for (int k = i; k <= j; ++k) a = a * 10 + X[k];
        set<int> ans{a, -a};
        for (int l = i; l < j; ++l) {
            auto F = run(i, l);
            auto G = run(l+1, j);
            for (int f: F) for (int g: G) {
                ans.insert(f + g);
                ans.insert(f - g);
                ans.insert(f * g);
            }
        }
        return ans;
    }

    void solve(istream& cin, ostream& cout) {
        int M, K;
        cin >> K >> M;

        set<int> ans;
        for (int a = 0; a < 10; ++a) {
            for (int b = 0; b < 10; ++b) {
                for (int c = 0; c < 10; ++c) {
                    for (int d = 0; d < 10; ++d) {
                        X = {a,b,c,d};
                        int s = 1000*a+100*b+10*c+d;
                        auto R = run(0, 3);
                        for (int r: R) {
                            for (int t: {K-r, K+r, r-K}) {
                                if (t >= 0 && t < 10000) {
                                    if (ans.size() < M) ans.insert(t * 10000 + s);
                                    if (ans.size() < M) ans.insert(s + t * 10000);
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int a: ans) {
            cout << setw(8) << setfill('0') << a << '\n';
        }
    }
};
