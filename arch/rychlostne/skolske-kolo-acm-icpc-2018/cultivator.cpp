#include "../l/lib.h"
 #include "../l/mod.h"
#include <numeric>  

class cultivator {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    cout << FieldMod{2}.pow(N) * (N-1) + 1 << endl;
}
};
