#include "../l/lib.h"
// #include "../l/mod.h"

class alterdist {
public:
    void solve(istream& cin, ostream& cout) {
        int x1, y1, x2, y2, d; cin >> x1 >> y1 >> x2 >> y2 >> d;
        int act = abs(x1-x2) + abs(y1-y2);
        if (act == d) {
            cout << "0\n";
            return;
        }

        if (act > d || (d-act)%2 == 1 || act == 1) {
            cout << "impossible\n";
            return;
        }

        if (abs(x1-x2) > 1) {
            cout << d - act - 1 + abs(y1-y2) << '\n';
            for (int y = min(y1,y2)-(d-act-2)/2; y <= max(y1,y2)+(d-act-2)/2; ++y) {
                cout << min(x1,x2)+1 << ' ' << y << '\n';
            }
        } else if (abs(y1-y2) > 1) {
            cout << d - act - 1 + abs(x1-x2) << '\n';
            for (int x = min(x1,x2)-(d-act-2)/2; x <= max(x1,x2)+(d-act-2)/2; ++x) {
                cout << x << ' ' << min(y1,y2)+1 << '\n';
            }
        } else if (d == 4) {
            cout << "impossible\n";
        } else {
            cout << d - 4 << endl;
            if ((x1 < x2) == (y1 < y2)) {
                for (int i = 0; i < (d-4)/2; ++i) {
                    cout << min(x1,x2) - i << ' ' << max(y1,y2) << '\n';
                    cout << max(x1,x2) + i << ' ' << min(y1,y2) << '\n';
                }
            } else {
                for (int i = 0; i < (d-4)/2; ++i) {
                    cout << min(x1,x2) - i << ' ' << min(y1,y2) << '\n';
                    cout << max(x1,x2) + i << ' ' << max(y1,y2) << '\n';
                }
            }
        }

    }
};
