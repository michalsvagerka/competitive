#include "../../../l/lib.h"
#include "../../../l/mod.h"

class C {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        cout << FieldMod{N}.pow((N-1)*(N-1)) << '\n';
    }
};
