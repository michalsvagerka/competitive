#include "../l/lib.h"
// #include "../l/mod.h"

class AGridGame {
public:
void solve(istream& cin, ostream& cout) {
    string S; cin >> S;
    int h = 0;
    int v = 0;
    for (char s : S) {
        if (s == '0') {
            cout << "1 " << (1+v%4) << '\n';
            ++v;
        } else {
            cout << "3 " << 1+2*(h%2) << '\n';
            ++h;
        }
    }
}
};
