#include "../l/lib.h"

constexpr int MX = 2000000000;
constexpr int DI = 5;

class BlindfoldedBullseye {
public:
    const string C = "CENTER";
    const string H = "HIT";
    const string M = "MISS";
    const string W = "WRONG";

    void solve(istream& cin, ostream& cout) {
        int T, A, B; cin >> T >> A >> B;
        bool wrong = false;
        for (int t = 0; t < T; ++t) {
            bool found = false;
            pii u = {0,0}, ans = {0,0};
            auto query = [&](int a, int b) {
                if (found || wrong) return false;
                cout << a << ' ' << b << endl;
                cerr << a << ' ' << b << endl;
                string S; cin >> S;
                if (S == W) wrong = true;
                if (S == C) {
                    ans = {a,b};
                    found = true;
                }
                return S == H;
            };
            for (int i = 1; i < DI && !found; ++i) {
                for (int j = 1; j < DI && !found; ++j) {
                    int a = -MX/2 + MX/DI*i;
                    int b = -MX/2 + MX/DI*j;
                    if (query(a,b)) u = {a,b};
                }
            }
            int loX = bsl(-MX/2, u.x, [&](int x) { return query(x, u.y); });
            u.x = loX;
            int loY = bsl(-MX/2, u.y, [&](int y) { return query(u.x, y); });
            int hiY = bsh(u.y, MX/2, [&](int y) { return query(u.x, y); });
            u.y = loY+(hiY-loY)/2;

            loX = bsl(-MX/2, u.x, [&](int x) { return query(x, u.y); });
            int hiX = bsh(u.x, MX/2, [&](int x) { return query(x, u.y); });
            u.x = loX+(hiX-loX)/2;

            while (!found && !wrong) {
                query(u.x, u.y);
            }
        }
    }
};
