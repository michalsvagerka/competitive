#include "../l/lib.h"

class H {
public:
    struct I {
        bool buy;
        int l, r;
    };

    void solve(istream& cin, ostream& cout) {
        vector<I> A;
        A.push_back({true, 0, 1023});
        for (int c = 1; c <= 15; ++c) {
            for (int p = 0; p < 16; ++p) {
                int before = 0;
                for (int i = p; i < p + c; ++i) before |= 1<<(i%16);
                int afterEat = before ^ (1<<p);
                A.push_back({false, before, afterEat});
                if (c <= 5) {
                    int afterBuy = before;
                    for (int i = p + c; i < p + c + 10; ++i) afterBuy |= 1<<(i%16);
                    A.push_back({true, before, afterBuy});
                }
            }
        }


        for (auto &a: A) {
            for (int i = 0; i < 4; ++i) cout << ".*"[!!(a.l & (1<<i))];
            cout << "|";
            for (int i = 4; i < 8; ++i) cout << ".*"[!!(a.l & (1<<i))];
            cout << " ";
            if (a.buy) cout << "buy"; else cout << "eat";
            cout << " ";
            for (int i = 0; i < 4; ++i) cout << ".*"[!!(a.r & (1<<i))];
            cout << "|";
            for (int i = 4; i < 8; ++i) cout << ".*"[!!(a.r & (1<<i))];
            cout << '\n';

            for (int i = 8; i < 12; ++i) cout << ".*"[!!(a.l & (1<<i))];
            cout << "|";
            for (int i = 12; i < 16; ++i) cout << ".*"[!!(a.l & (1<<i))];
            cout << "     ";
            for (int i = 8; i < 12; ++i) cout << ".*"[!!(a.r & (1<<i))];
            cout << "|";
            for (int i = 12; i < 16; ++i) cout << ".*"[!!(a.r & (1<<i))];
            cout << '\n';
            cout << "---\n";
        }
    }
};
