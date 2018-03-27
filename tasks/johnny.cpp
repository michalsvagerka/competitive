#include "../l/lib.h"
// #include "../l/mod.h"

class johnny {
public:
    set<ui> sqrt(ui a) {
        ui r = 1;
        set<ui> ans;
        while (a % 4 == 0) { r *= 2; a /= 4; }
        if (a % 8 == 1) {
            for (ui x: {1u,3u}) {
                for (int k = 3; k < 32; ++k) {
                    ui i = (x*x - a)/(1<<k) % 2;
                    x = x + i*(1<<(k-1));
                }
                ans.insert(x*r);
                ans.insert((-x)*r);
            }
        }
        return ans;
    }

    bool canDiv(ui a, ui b) {
        if (a == 0) return true;
        while (a%2 == 0 && b%2 == 0) {
            a /= 2; b /= 2;
        }
        return (b%2 == 1);
    }

    void solve(istream& cin, ostream& cout) {
        ui T; cin >> T;
        for (int t = 0; t < T; ++t) {
            ui a, b, c;
            cin >> a >> b >> c;
            ui d = b * b - 4 * a * c;
            bool ok = false;
            if (d == 0) {
                ok = canDiv((-b) & 0xffff, 2*a);
            } else {
                set<ui> S = sqrt(d);
                for (ui s:S) {
                    ok |= canDiv(-b + s, 2 * a);
                    ok |= canDiv(-b - s, 2 * a);
                }
            }
            cout << (ok ? "YES" : "NO") << endl;

        }
    }

};
