#include "../l/lib.h"

class AVladikAndFlights {
public:
    void solve(istream& cin, ostream& cout) {
        int N, A, B;
        cin >> N >> A >> B;
        string S; cin >> S;
        cout << (S[A-1] ^ S[B-1]) << endl;
    }
};
