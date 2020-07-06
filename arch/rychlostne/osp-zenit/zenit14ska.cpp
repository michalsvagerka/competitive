#include "../l/lib.h"

class zenit14ska {
public:
    void solve(istream& cin, ostream& cout) {
        string A, B; cin >> A >> B;
        int N = A.size() + B.size() + 8;
        cout << string(N, '*') << '\n';
        cout << '*' << string(N-2, ' ') << "*\n";
        cout << "*  " << A << "  " << B << "  *\n";
        cout << '*' << string(N-2, ' ') << "*\n";
        cout << string(N, '*') << '\n';
    }
};
