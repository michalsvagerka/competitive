#include "../l/lib.h"
// #include "../l/mod.h"

class P4 {
public:
    void solve(istream& cin, ostream& cout) {
        string T;
        while (getline(cin, T)) {
            while (true) {
                stringstream Q;
                for (int i = 0; i < T.size(); i += 2) {
                    int a = T[i] - '0';
                    char b = T[i + 1];
                    Q << string(a, b);
                }
                T = Q.str();
                if (T.size() <= 4) {
                    cout << T << endl;
                    break;
                }
            }
        }

    }
};
