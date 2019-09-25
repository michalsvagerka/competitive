#include "../l/lib.h"

class AXORCircle {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        map<int, int> C;
        for (int a: A) C[a]++;
        if (C.count(0) && C[0] == N) {
            cout << "Yes\n";
        } else if (N % 3 != 0) {
            cout << "No\n";
        } else if (C.size() == 2) {
            if (C.count(0) && C[0] == N/3) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        } else if (C.size() == 3) {
            auto a = *C.begin();
            auto b = *next(C.begin());
            auto c = *next(next(C.begin()));
            if ((a.x ^ b.x ^ c.x) != 0) {
                cout << "No\n";
            } else if (a.y != N/3 || b.y != N/3 || c.y != N/3) {
                cout << "No\n";
            } else {
                cout << "Yes\n";
            }
        } else {
            cout << "No\n";
        }
    }
};
