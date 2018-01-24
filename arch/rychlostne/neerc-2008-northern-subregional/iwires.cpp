#include "../l/lib.h"
// #include "../l/mod.h"

class iwires {
public:
    void solve(istream& cin, ostream& cout) {
        ui N; cin >> N;
        cout << "Yes\n";
        char c;
        for (ui i = 0; i < N; ++i) {
            cin >> c;
            string s; getline(cin, s);
            cout << c << '|';
        }
        cout << '~' << c << endl;
    }
};
