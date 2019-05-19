#include "../l/lib.h"
// #include "../l/mod.h"

class BGameWithModulo {
public:
void solve(istream& cin, ostream& cout) {
    string S; cin >> S;
    while (S == "start") {
        cout << "? 0 1" << endl;
        cin >> S;
        if (S == "x") {
            cout << "! 1" << endl;
        } else {
            int l, r;
            for (int i = 0; i < 29; ++i) {
                cout << "? " << (2<<i)-1 << ' ' << (4<<i)-1 << endl;
                cin >> S;
                if (S == "e") return;
                
                if (S == "x") {
                    // mod is between 2<<i and (4<<i)-1
                    l = 2<<i;
                    r = (4<<i)-1;
                    break;
                }
            }
            
            int a = bsl(l, r, [&](int x) {
                cout << "? " << l-1 << ' ' << x << endl;
                cin >> S;
                return S=="x";
            });
            
            cout << "! " << a << endl;
        }

        cin >> S;
    }
}
};
