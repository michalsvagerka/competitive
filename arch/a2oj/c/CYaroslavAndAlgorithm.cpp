#include "../l/lib.h"

class CYaroslavAndAlgorithm {
public:
    void solve(istream& cin, ostream& cout) {
        for (int i = 0; i < 9; ++i) cout << i << "??" << "<>" << i+1 << endl;
        cout << "9??" << ">>" << "??0" << endl;
        cout << "??" << "<>" << "1" << endl;
        for (int i = 0; i < 10; ++i) cout << '?' << i << ">>" << i << '?' << endl;
        cout << "?>>??" << endl;
        cout << ">>?" << endl;
    }
};
