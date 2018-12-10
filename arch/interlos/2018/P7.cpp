#include "../l/lib.h"
// #include "../l/mod.h"

class P7 {
public:
void solve(istream& cin, ostream& cout) {
    int R = 30, C = 30;
    vector2<char> P(R,C); cin >> P;

    int r = 15, c = 15;
    string S; cin >> S;
    for (char s: S) {
        switch (s) {
            case 'U':
                r--;
                break;
            case 'D':
                r++;
                break;
            case 'L':
                c--;
                break;
            case 'R':
                c++;
                break;
            case 'X':
                cout << P[r][c];
        }
    }
    cout << endl;
}
};
