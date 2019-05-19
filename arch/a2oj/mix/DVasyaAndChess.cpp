#include "../l/lib.h"
// #include "../l/mod.h"

class DVasyaAndChess {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    if (N % 2 == 1) {
        cout << "black\n";
    } else {
        cout << "white\n1 2\n";
    }
}
};
