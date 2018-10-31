#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    int L = 0;
    int R = 1e9;
    cout << "0 1" << endl;
    string W; cin >> W;
    for (int i = 0; i < N-1; ++i) {
        cout << (L + R) / 2 << ' ' << 1 << endl;
        string S; cin >> S;
        if (S == W) {
            L = (L+R)/2;
        } else {
            R = (L+R)/2;
        }
    }
    
    cout << L << " 0 " << R << ' ' << 2 << endl;
}
};
