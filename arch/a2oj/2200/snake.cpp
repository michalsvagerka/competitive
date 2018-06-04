#include "../l/lib.h"
// #include "../l/mod.h"

class snake {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        for (int i = 0; i < N; ++i) {
            if (i%2==0) {
                cout << string(M,'#') << '\n';
            } else if (i%4==1) {
                cout << string(M-1,'.') << '#' << '\n';
            } else {
                cout << '#' << string(M-1,'.') << '\n';
            }
        }
    }
};
