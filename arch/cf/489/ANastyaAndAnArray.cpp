#include "../../../l/lib.h"

class ANastyaAndAnArray {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        set<int> B;
        for (int a: A) if (a != 0) B.insert(a);
        cout << B.size() << '\n';
    }
};
